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
    void initialize(const string& api,const string& name,const unsigned int& num){assignment()=num; apiKey()=api; userName()=name;}
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
        POD()=delete;//Prevents instantiation
        /**
         * Uses Easy CURL library to execute a simple POST request,
         * of "json_of_ds" to "url".
         *
         * @param url The url destination for the post command
         * @param json_of_ds The JSON string of the data structure representation
         * @throw string Thrown if curl post fails
         */
        static void post(const string& url,const string& json_of_ds)
        {
            curl_global_init(CURL_GLOBAL_ALL); // first form the full url
            CURL* curl = curl_easy_init(); // get a curl handle
            if (curl)
            {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // set the URL receiving our POST

                curl_easy_setopt(curl, CURLOPT_WRITEDATA, nullptr); //pass pointer to callback function
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunction); //sends all data to this function

                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_of_ds.c_str()); // Now specify the POST data
                curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_of_ds.length()); // Now specify the POST data size
                curl_easy_setopt(curl, CURLOPT_POST, 1); //  a post request
                curl_easy_setopt(curl, CURLOPT_HEADER, 1L); // send header

                struct curl_slist* headers = nullptr;
                headers = curl_slist_append(headers, "Content-Type: application/json");
                headers = curl_slist_append(headers, "Accept: application/json");
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                CURLcode res = curl_easy_perform(curl); // Perform the request, res will get the return code

                if (res != CURLE_OK){throw "curl_easy_perform() failed.\nCurl Error Code "+to_string(res)+": "+curl_easy_strerror(res)+"\n";}
                curl_easy_cleanup(curl);
            }
            else{throw "curl_easy_init() failed!\nNothing posted to server.\n";}
        }
        /** CURL WRITE FUNCTION PLACEHOLDER */
        static size_t curlWriteFunction(char *contents, size_t size, size_t nmemb, void *userdata){return (contents && !userdata)? size*nmemb : size*nmemb;}//userdata is of pointer type passed to WRITEDATA
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
        try{POD::post(url_to_server, ds_json); cout<< "Success: Assignment posted to the server. Check out your visualization at \n\n\t"+url_to_vis <<endl<<endl; part++;}
        catch(const string& error_str){cerr << "Posting assignment to the server failed!" <<endl<< error_str <<endl<< "Generated JSON: " << ds_json <<endl;}
    }
}//end of Bridges namespace
}//end of bridges namespace
#endif
