
#ifndef CONNECTOR_H 

#define CONNECTOR_H

#include <string>
#include <iostream>
#include <curl/curl.h>

using namespace std;

#include "Element.h"
#include "ADTVisualizer.h"

class Connector {

	private:
	    string server_url;
//	    Executor http_connection;
//	    bool debug = false;

	public:
	    
	    Connector() {
			server_url = "http://bridges-cs.herokuapp.com";
//			server_url = "http://127.0.0.1:3000";
	    }
	    
	    /* Accessors and Mutators */
	    
	    /**
	     * Get the current  base URL for the DataFormatters server 
		 * (with no ending /)
	     * @return
	     **/
		string getServerURL() {
			return server_url;
		}
	
		/**
		 * Set the current base URL for the DataFormatters server (with no 
		 * 	ending /)
		 * @param server_url
		 */
		void setServerURL(string url) {
								// must consider validating this url
			server_url = url;
		}

		/** 
		 * 	Execute a simple POST request with relative paths, 
		 *	of request parameters. 
		 *	
		 *  Uses the Curl library 
		 *
		 **/

	    void post(string url, string json_of_ds) {

						// first form the full url
			cout << "url: " << url << endl;
			cout << "\nJSON String:" << json_of_ds << endl;
  			curl_global_init(CURL_GLOBAL_ALL);

										// get a curl handle 
			CURL *curl = curl_easy_init();
			if (curl) {
						// 	set the URL receiving our POST. 
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
						//  a post request
				curl_easy_setopt(curl, CURLOPT_POST, 1);
						// Now specify the POST data
   				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_of_ds.c_str());
						// Now specify the POST data size
cout << "Size of Json: " << json_of_ds.length() << endl;
   				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_of_ds.length());
						// Perform the request, res will get the return code 
				CURLcode res = curl_easy_perform(curl);
cout << "Response Code: " << res << endl;
						// Check for errors 
				if (res != CURLE_OK) {
					cout << "curl_easy_perform() failed: Code " << res << endl; 
					curl_easy_strerror(res);
				}
				else 
					cout <<  "Seemed to work.." << std::endl;

				curl_easy_cleanup(curl);
			}
		}

};

#endif
