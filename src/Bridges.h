#ifndef BRIDGES_H
#define BRIDGES_H

#include <curl/curl.h> //curl

#include "DataStructure.h" //string, using std

namespace bridges{
/**
 * @brief This class contains methods to connect and transmit a user's data structure representation to the Bridges server (up to 5000 elements)
 *
 * @author Kalpathi Subramanian
 * @date  7/26/15
 */
namespace Bridges
{
    /** @return Reference to flag indicating if JSON should be printed upon visualization */
    bool& visualizeJSON(){static bool flag = false; return flag;} //having a function can help hide implimentation details
    /** @return Reference to member holding the username credential for the server */
    string& userName(){static string user; return user;} //having a function can help hide implimentation details
    /** @return Reference to member holding the api key credential for the server */
    string& apiKey(){static string key; return key;}//having a function can help hide implimentation details
    /** @return Reference to member holding the assignment number for holding the visualization on the server */
    unsigned int& assignment(){static unsigned int num = 0; return num;} //having a function can help hide implimentation details
    /** @return Reference to member holding the array size of the data structure handle */
    unsigned int& array_size(){static unsigned int size = 1; return size;}//having a function can help hide implimentation details
    /** @return Reference to member holding the data structure handle */
    DataStructure*& ds_handle(){static DataStructure* handle = nullptr; return handle;}//having a function can help hide implimentation details
    /**
     * Sets Bridges assignment to "num", api key to "api" and username to "name".
     *
     * @param assignm The assignment number
     * @param api The API key
     * @param user The username
     */
    void initialize(const unsigned int& num,const string& name,const string& api){assignment()=num; apiKey()=api; userName()=name;}
    /**
     * Sets the data structure handle to "handle" with an array size of "size" (default of 1).
     * User is resposible for memory management of data type handle.
     *
     * @param handle The handle of the data structure
     * @param size The array size of this data structure
     */
    void setDataStructure(DataStructure* handle, const unsigned int& size=1){ds_handle() = handle; array_size() = size;}
    void visualize();
    /** @brief This is a detail class for the Bridges namespace and is not intended for external use */
    class POD //Plain Old Data
    {
        friend void Bridges::visualize(); //Used for access to this class' private functions
        friend vector<Earthquake> Bridges::getEarthquakes(int num);
        POD()=delete;//Prevents instantiation
        /** CURL WRITE FUNCTION PLACEHOLDER */
        static size_t curlWriteFunction(void *contents, size_t size, size_t nmemb, void *results)
        {
            size_t handled = size*nmemb;
            if(results)
            {
                ((string*)results)->append((char*)contents);
            }
            return handled;
        }
        /**
         * Uses Easy CURL library to execute a simple request.
         *
         * @param url The url destination for the request
         * @param headers The headers for the request
         * @param data The content sent in POST requests
         * @throw string Thrown if curl request fails
         */
        static string makeRequest(const string& url,const vector<string>& headers, const string& data = "")
        {
            string results;
            curl_global_init(CURL_GLOBAL_ALL); // first load curl enviornment (only need be called once in entire session tho)
            CURL* curl = curl_easy_init(); // get a curl handle
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // set the URL to GET from

                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &results); //pass pointer to callback function
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunction); //sends all data to this function

                if(data.length() > 0)
                {
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str()); // Now specify the POST data
                    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length()); // Now specify the POST data size
                    curl_easy_setopt(curl, CURLOPT_POST, true); //  a post request
                }

                struct curl_slist* curlHeaders = nullptr;
                for(const string& header : headers)
                {
                    curlHeaders = curl_slist_append(curlHeaders, header.c_str());
                }
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
                CURLcode res = curl_easy_perform(curl); // Perform the request, res will get the return code
                if (res != CURLE_OK){throw "curl_easy_perform() failed.\nCurl Error Code "+to_string(res)+": "+curl_easy_strerror(res)+"\n";}
                curl_easy_cleanup(curl);
            }
            else{throw "curl_easy_init() failed!\nNothing retrieved from server.\n";}
            return results;
        }

        /**
         * Builds the JSON string from the data structure handle
         * Prints complete JSON if "visualizeJSON" flag is enabled.
         *
         * @return Completed JSON
         */
        static string build_JSON()
        {
            if(!Bridges::ds_handle()){throw "Error: build_JSON called with null data structure";}
            const pair<string,string> json_nodes_links = Bridges::ds_handle()->getDataStructureRepresentation(Bridges::array_size());
            string s_final =
                OPEN_CURLY +
                    QUOTE + "version" + QUOTE + COLON + QUOTE + "0.4.0" + QUOTE + COMMA +
                    QUOTE + "visual"  + QUOTE + COLON + QUOTE + Bridges::ds_handle()->getDStype() + QUOTE + COMMA +
                    QUOTE + "nodes"   + QUOTE + COLON + "[" + json_nodes_links.first   + "]" + COMMA +
                    QUOTE + "links"   + QUOTE + COLON + "[" + json_nodes_links.second  + "]" +
                CLOSE_CURLY;

            if (Bridges::visualizeJSON()){cout << "JSON String:\t" << s_final << endl;}
            return s_final;
        }
    };//end of POD class
    vector<Earthquake> getEarthquakes(int num)
    {
        static const int MAX_EQS = 500;
        static vector<Earthquake> allEQs;
        if(allEQs.empty())
        {
            allEQs.reserve(MAX_EQS);
            string results = POD::makeRequest("http://earthquakes-uncc.herokuapp.com/eq/latest/"+to_string(MAX_EQS),{"Accept: application/json"});

            ///Now Have to Parse JSON String to add Earthquake objects
            ///JSON encoding would be preferable, but just performs string searches
            ///Highly dependent upon datas schema/order
            string props, loc, date, url, title, searchKey;
            double lng, lat, mag, start, end;
            while(results.length() > 0)
            {
                //Gets lng and lat from coordinates
                searchKey = QUOTE+"coordinates"+QUOTE+COLON+"[";
                start = results.find(searchKey)+searchKey.length();
                end = results.find(",",start);
                lng = stod(results.substr(start,end-start));
                start = end+1;
                end = results.find(",",start);
                lat = stod(results.substr(start,end-start));

                //Gets substr of properties, everything between and including { }
                searchKey = QUOTE+"properties"+QUOTE+COLON;
                start = results.find(searchKey)+searchKey.length();
                end = results.find("},{");
                end = end == string::npos?results.length():end+1; //IF LAST
                props = results.substr(start,end-start);
                results = results.substr(end);

                    searchKey = QUOTE+"mag"+QUOTE+COLON;
                    start = props.find(searchKey)+searchKey.length();
                    end = props.find(",",start);
                mag = stod(props.substr(start,end-start));

                    searchKey = QUOTE+"place"+QUOTE+COLON+QUOTE;
                    start = props.find(searchKey)+searchKey.length();
                    end = props.find(QUOTE+",",start);
                loc = props.substr(start,end-start);

                    searchKey = QUOTE+"time"+QUOTE+COLON+QUOTE;
                    start = props.find(searchKey)+searchKey.length();
                    end = props.find(QUOTE+",",start);
                date = props.substr(start,end-start);

                    searchKey = QUOTE+"url"+QUOTE+COLON+QUOTE;
                    start = props.find(searchKey)+searchKey.length();
                    end = props.find(QUOTE+",",start);
                url = props.substr(start,end-start);

                    searchKey = QUOTE+"title"+QUOTE+COLON+QUOTE;
                    start = props.find(searchKey)+searchKey.length();
                    end = props.find(QUOTE+",",start);
                title = props.substr(start,end-start);

                allEQs.push_back(Earthquake("USGSeq magnitude "+to_string(mag)+" "+title,date,mag,lng,lat,loc,title,url,props));
            }
        }
        if(num > MAX_EQS)
        {
            cerr << "Warning! Earthquake request volume exceeded. Range must be [0-"<<MAX_EQS<<"]"<<endl;
            num=MAX_EQS;
        }
        return vector<Earthquake>(allEQs.begin(),allEQs.begin()+num); //returns copy of range
    }
    /** Sends relevant data handle information to the server, and upon successful completion, prints the URL to display the Bridges visualization. */
    void visualize()
    {
        static unsigned int lastAssign = 0; static int part = 0; static const string SERVER_URL = "http://bridges-cs.herokuapp.com";
        if(assignment() != lastAssign){lastAssign=assignment(); part=0;} //resets part if different using assignment number

        if(part==99){cout<<"Visualization has been performed maximum number of times for this assignment, no action taken.."<<endl;return;}//rollover will occur
        if(!ds_handle()){cerr<<"Error: visualizer called with a nullptr data structure... visualization not performed."; return;}

        // form the url for the http post request
        const string url_to_server = SERVER_URL + "/assignments/" + to_string(assignment()) + "." + (part>9?"":"0") + to_string(part) + "?apikey=" + apiKey();
        const string url_to_vis =    SERVER_URL + "/assignments/" + to_string(assignment()) + "/" + userName();

        string ds_json = POD::build_JSON();
        try{POD::makeRequest(url_to_server, {"Content-Type: application/json"},ds_json); cout<< "Success: Assignment posted to the server. Check out your visualization at \n\n\t"+url_to_vis <<endl<<endl; part++;}
        catch(const string& error_str){cerr << "Posting assignment to the server failed!" <<endl<< error_str <<endl<< "Generated JSON: " << ds_json <<endl;}
    }
}//end of Bridges namespace
}//end of bridges namespace
#endif
