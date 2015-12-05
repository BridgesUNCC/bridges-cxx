#ifndef BRIDGES_H
#define BRIDGES_H

#include <curl/curl.h> //curl

#include "DLelement.h" //string, unordered map, out of range, using std
#include "BSTElement.h"
#include "GraphAdjList.h"
#include "GraphAdjMatrix.h"

namespace bridges {
/**
 * @brief This class contains methods to connect and transmit a user's
 * 	data structure representation to the Bridges server
 *
 * This class contains the needed initialization functions for BRIDGES
 * and the needed methods to connect to the server
 *
 * @author Kalpathi Subramanian (C++ port)
 * @date  7/26/15
 */
class Bridges
{
    /* This class is essentialy a namespace.
    C++ doesn't support access specifiers in namespaces,
    so in order to not have 'private' members accessable by users,
    a class was used, instantiation was denied, and
    all functions and varaibles have been declared static */
    private:
        Bridges(); //Protects Constructor
		enum struct DS_Type {None, Array, SLList, DLList, Tree, BST, Graph_M, Graph_L};
		/** Nested class used to hold a collective of variables as static without multiple static declarations */
		struct POD //Plain Old Data
		{
		    void* dataStruct = nullptr; //pointer from reference of elements of graphs, so user is resposible mem management
            double assignment = 0; // assignment number and  fractional part (0-100 supported)
            string key, userName;   // application id; user id
            DS_Type dsType = DS_Type::None; //dataStruct pointed to reference type
            const string SERVER_URL = "http://bridges-cs.herokuapp.com";
            bool visualizeJSON = false; //flags printing of generated JSON
            int array_size = 0;
		};//end of POD struct
		static POD pod;
	public:
		/**
		 * Sets Bridges assignment to "num", api key to "api" and username to "name".
		 * If assignment number is not given, the default of 1 will be used.
		 *
		 * @param assignm The assignment number
		 * @param app_id The API key
		 * @param user The username
		 */
		static void initialize(const string& api,const string& name,const int& num=1)
		{
            setAssignment(num); setKey(api); setUserName(name);
		}
		/**
		 * Returns the size of the array
		 *
		 * @return The array size
		 */
		static int getArraySize(){return pod.array_size;}
		/**
		 * Returns flag that controls if the JSON is to be printed when generated
		 *
 		 * @return The JSON visualization flag
 		 */
		static bool isVisualizeJSON(){return pod.visualizeJSON;}
		/**
		 * Sets JSON visualization flag to "flag"
		 *
 		 * @param flag The JSON visualization flag
 		 */
		static void setVisualizeJSON(const bool& flag){pod.visualizeJSON = flag;}
		/**
		 * Returns the visualizer type
		 *
		 * @return The visualizer type
		 */
		static string getVisualizerType()
		{
            switch(pod.dsType)
            {
            case DS_Type::None: return "None";
            case DS_Type::Array: return "Array";
            case DS_Type::SLList: return "SinglyLinkedList";
            case DS_Type::DLList: return "DoublyLinkedList";
            case DS_Type::Tree: return "BinaryTree";
            case DS_Type::BST: return "BinarySearchTree";
            case DS_Type::Graph_M: return "GraphAdjacencyMatrix";
            case DS_Type::Graph_L: return "GraphAdjacencyList";
            default: return "Unknown";
            }
		}
		/**
		 * Returns the assignment number
		 *
		 * @return The assignment number
		 */
		static double getAssignment(){return pod.assignment;}
		/**
		 * Sets the assignment number to "num"
		 *
		 * @param num The assignment number
		 */
		static void setAssignment(const int& num)
		{
			if (num < 0)
            {
				cerr << "Assignment id is negative! Received " << num << "..exiting.." << endl;
				exit(EXIT_FAILURE);
			}
			pod.assignment = num;
		}
		/**
		 * Returns the username
		 *
		 * @return The username
		 */
		static string getUserName(){return pod.userName;}
		/**
		 * Sets the username to "name"
		 *
		 * @param name The username
		 */
		static void setUserName(const string& name){pod.userName = name;}
		/**
		 * Returns the API key
		 *
		 * @return The API key
		 */
		static string getKey(){return pod.key;}
		/**
		 * Sets the API key to "api"
		 *
		 * @param api The api key
		 */
		static void setKey(const string& api){pod.key = api;}
        /**
		 * Sets the data type handle to Array "arr".
		 * User is resposible for memory management of previous data type handle.
		 *
		 * @param arr The array pointer
		 * @param size The array size
		 */
        template <typename E>
		static void setDataStructure(Element<E> arr[],const int& size)
		{
			if(size > 0)
            {
                setDataHandle(arr);
				setArraySize(size);
				setDataType(DS_Type::Array);
			}
			else
			{
				setDataType(DS_Type::None);
				cerr << "Warning: Array is of zero or negative size... Data handle unset" << endl;
			}
		}
		/**
		 * Sets the data type handle to Singly Linked List "head".
		 * User is resposible for memory management of data type handle.
		 *
		 * @param head The singly linked list
		 */
        template <typename E>
		static void setDataStructure(SLelement<E>* head)
		{
            setDataHandle(head);
            setDataType(DS_Type::SLList);
		}
		/**
		 * Sets the data type handle to Doubly Linked List "head".
		 * User is resposible for memory management of data type handle.
		 *
		 * @param head The doubly linked list
		 */
        template <typename E>
		static void setDataStructure(DLelement<E>* head)
		{
            setDataHandle(head);
            setDataType(DS_Type::DLList);
		}
		/**
		 * Sets the data type handle to Binary Tree "root".
		 * User is resposible for memory management of data type handle.
		 *
		 * @param root The binary tree
		 */
        template <typename E>
		static void setDataStructure(TreeElement<E>* root)
		{
            setDataHandle(root);
            setDataType(DS_Type::Tree);
		}
		/**
		 * Sets the data type handle to Binary Search Tree "root".
		 * User is resposible for memory management of data type handle.
		 *
		 * @param root The binary search tree
		 */
        template <typename K, typename E>
		static void setDataStructure(BSTElement<K,E>* root)
		{
            setDataHandle(root);
            setDataType(DS_Type::BST);
		}
		/**
		 * Sets the data type handle to Graph Adjacency List "graph".
		 * User is resposible for memory management of data type handle.
		 *
		 * @param graph The graph adjacency list
		 */
        template <typename K, typename E>
		static void setDataStructure(GraphAdjList<K, E>* graph)
		{
            setDataHandle(graph);
            setDataType(DS_Type::Graph_L);
		}
		/**
		 * Sets the data type handle to Graph Adjacency Matrix "graph".
		 * User is resposible for memory management of data type handle.
		 *
		 * @param graph The graph adjacency matrix
		 */
        template <typename K, typename E>
		static void setDataStructure(GraphAdjMatrix<K, E>* graph)
		{
            setDataHandle(graph);
            setDataType(DS_Type::Graph_M);
		}
		/**
		 * Sends relevant data handle information to the server,
		 * and upon successful completion, prints the URL to
		 * display the Bridges visualization.
		 *
		 * Must be called after initialize and setDataStructure have been called.
		 * @warning Template arguments must be the same as used in setDataStructure
		 */
        template <typename E, typename K=int>
		static void visualize()
		{
		    if((int)getAssignment() != (int)(getAssignment()+.01)) //rollover occured
            {
                cout << "Visualization has been performed maximum number of times for this assignment, no action taken..";
                return;
            }
                         //ex: 1.000000         ex: 1.00
            string num = to_string(getAssignment()); num.erase(num.size()-4);
			// form the url for the http post request
			const string url_to_server = pod.SERVER_URL + "/assignments/" + num + "?apikey=" + getKey();
			const string url_to_vis =    pod.SERVER_URL + "/assignments/" + to_string(static_cast<int>(getAssignment())) + "/" + getUserName();

            pair<string,string> json_nodes_links;
            switch(pod.dsType)
            {
            case DS_Type::Array:
                json_nodes_links = static_cast<Element<E>*>(getDataHandle())->getDataStructureRepresentation(getArraySize()); break;
            case DS_Type::SLList:
                json_nodes_links = static_cast<SLelement<E>*>(getDataHandle())->getDataStructureRepresentation(); break;
            case DS_Type::DLList:
                json_nodes_links = static_cast<DLelement<E>*>(getDataHandle())->getDataStructureRepresentation(); break;
            case DS_Type::Tree:
                json_nodes_links = static_cast<TreeElement<E>*>(getDataHandle())->getDataStructureRepresentation(); break;
            case DS_Type::BST:
                json_nodes_links = static_cast<BSTElement<K, E>*>(getDataHandle())->getDataStructureRepresentation(); break;
            case DS_Type::Graph_M:
                json_nodes_links = static_cast<GraphAdjMatrix<K,E>*>(getDataHandle())->getDataStructureRepresentation(); break;
            case DS_Type::Graph_L:
                json_nodes_links = static_cast<GraphAdjList<K,E>*>(getDataHandle())->getDataStructureRepresentation(); break;
            default: // None
                cerr << "Error! JSON not generated. Unset data structure" << endl; return;
            }
            string ds_json = build_JSON(json_nodes_links.first,json_nodes_links.second);
            try
            {
                post(url_to_server, ds_json);
                cout << "Success: Assignment posted to the server. Check out your visualization at \n\n\t"+url_to_vis << endl << endl;
                pod.assignment+=.01;
            }
            catch(const string& error_str)
            {
                cerr << "Posting assignment to the server failed!" << endl
                     << error_str << endl
                     << "Generated JSON(" << getVisualizerType() << "): " << ds_json << endl;
            }
		}
	private:
		/**
         * Returns the data handle
         *
         * @return The data handle
         */
        static void* getDataHandle(){return pod.dataStruct;}
        /**
         * Sets the data handle to "handle"
         *
         * @param The data handle
         */
        static void setDataHandle(void* handle){pod.dataStruct = handle;}
        /**
		 * Sets visualizer type to "vis_type"
		 *
		 * @param vis_type The type of Bridges visualization
		 */
		static void setDataType(const DS_Type& type){pod.dsType = type;}
		/**
		 * Returns the visualizer type
		 *
		 * @return The visualizer type
		 */
		static DS_Type getDataType(){return pod.dsType;}
		/**
		 * Sets the array size to "size" for use by other functions
		 *
		 * @param size The array size
		 */
		static void setArraySize(const int& size){pod.array_size = size;}
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

				if (res != CURLE_OK)// Check for errors
                {
					throw "curl_easy_perform() failed.\nCurl Error Code "+to_string(res)+": "+curl_easy_strerror(res)+"\n";
				}
				curl_easy_cleanup(curl);
			}
			else
            {
				throw "curl_easy_init() failed!\nNothing posted to server.\n";
			}
		}
		/** CURL WRITE FUNCTION PLACEHOLDER **/
		static size_t curlWriteFunction(char *contents, size_t size, size_t nmemb, void *userdata)//userdata is of pointer type passed to WRITEDATA
		{
		    if(contents && !userdata)
            {
                return size * nmemb;
            }
            return size * nmemb;
		}
		/**
		 * Builds the JSON string from "nodes_JSON" and "links_JSON"
		 * Prints complete JSON if "visualizeJSON" flag is enabled.
		 *
		 * @param nodes_JSON JSON string representation of nodes
		 * @param links_JSON JSON string representation of links
		 * @return Completed JSON
		 */
		static string build_JSON(const string& nodes_JSON,const string& links_JSON)
		{
			string s_final =
				OPEN_CURLY +
					QUOTE + "name"    + QUOTE + COLON + QUOTE + "edu.uncc.cs.bridges" + QUOTE + COMMA +
					QUOTE + "version" + QUOTE + COLON + QUOTE + "0.4.0"               + QUOTE + COMMA +
					QUOTE + "visual"  + QUOTE + COLON + QUOTE + getVisualizerType()   + QUOTE + COMMA +
                    QUOTE + "nodes"   + QUOTE + COLON + OPEN_PAREN + nodes_JSON + CLOSE_PAREN + COMMA +
                    QUOTE + "links"   + QUOTE + COLON + OPEN_PAREN + links_JSON + CLOSE_PAREN +
                CLOSE_CURLY;

			if (pod.visualizeJSON){cout << "JSON String:\t" << s_final << endl;}
			return s_final;
		}
}; //end of Bridges class
Bridges::POD Bridges::pod = Bridges::POD();
}//end of bridges namespace
#endif
