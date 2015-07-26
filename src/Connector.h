#ifndef CONNECTOR_H 

#define CONNECTOR_H

#include <string>
#include <iostream>
#include <curl/curl.h>

using namespace std;

#include "Element.h"
#include "ADTVisualizer.h"
namespace bridges {
/**
 *	@brief  The role of this class is to transmit the JSON of a data structure
 *			to the BRIDGES server

 *	 This class is responsible for transmitting JSON representation of  
 *   the user's data structure to the  BRIDGES server, prior to visualization
 *   The JSON is packaged and transmitted using the Easy CURL library
 *
 *	 @author Kalpathi Subramanian (C++ port)
 *
 *	 @date 7/26/15
 *
 **/

class Connector {

	private:
	    string server_url;

	public:
	    
	    /**
		 * Constructor - sets the server url
		 **/

	    Connector() {
//			server_url = "http://bridges-cs.herokuapp.com";
			server_url = "http://127.0.0.1:3000";
	    }
	    
	    /** 
		 * 	Accessors 
		 **/
	    
	    /**
		 *
	     * Get the current  base URL for the DataFormatters server 
		 * (with no ending /)
	     * @return string
		 *
	     **/
		string getServerURL() {
			return server_url;
		}
	
		/**
		 * 	Set the current base URL for the DataFormatters server (with no 
		 * 		ending /)
		 * 	@param server_url
		 **/
		void setServerURL(string url) {
								// must consider validating this url
			server_url = url;
		}

		/** 
		 * 	Execute a simple POST request with relative paths, 
		 *	of request parameters. 
		 *	
		 *  Uses the Easy CURL library 
		 *
		 **/

	    void post(string url, string json_of_ds) {

						// first form the full url
  			curl_global_init(CURL_GLOBAL_ALL);

										// get a curl handle 
			CURL *curl = curl_easy_init();
			if (curl) {
									// 	set the URL receiving our POST. 
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
									// Now specify the POST data
   				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_of_ds.c_str());
									// Now specify the POST data size
   				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 
									json_of_ds.length());
									//  a post request
				curl_easy_setopt(curl, CURLOPT_POST, 1);
						// ask libcurl to show us the verbose output 
//				curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
						// send header
				curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
				struct curl_slist *headers=NULL;
				headers = curl_slist_append(headers, "Content-Type: application/json");
				headers = curl_slist_append(headers, "Accept: application/json");
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
									// Perform the request, res will 
									// get the return code 
				CURLcode res = curl_easy_perform(curl);
									// Check for errors 
				if (res != CURLE_OK) {
					cout << "curl_easy_perform() failed: Posting assignment "
						<< "to the  server failed. Curl Error Code: " 
						<< res << endl << endl; 
					curl_easy_strerror(res);
				}
				else 
					cout <<  "Success. Assignment Posted to the server.." 
															<< endl;

				curl_easy_cleanup(curl);
			}
		}

};

}
#endif
