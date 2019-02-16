#ifndef SERVER_COMM_H
#define SERVER_COMM_H

#include <string>
#include <vector>
using namespace std;
#include <curl/curl.h> //curl
#include "./data_src/EarthquakeUSGS.h"
#include "./data_src/Game.h"
#include "./data_src/Shakespeare.h"
#include "./data_src/GutenbergBook.h"
#include "./data_src/CancerIncidence.h"
#include "./data_src/ActorMovieIMDB.h"
#include "./data_src/Song.h"

namespace bridges {
	/**
	 *	@brief This is a detail class for the Bridges namespace and
	 *			is not intended for external use
	 */
	class ServerComm {
			//Used to access to this class private functions
			friend class Bridges;
			friend class DataSource;

			ServerComm() = delete; //Prevents instantiation

			/** CURL WRITE FUNCTION PLACEHOLDER (TODO - Replace with something
			 * 		better)
			 */
			static size_t curlWriteFunction(void *contents, size_t size,
				size_t nmemb, void *results) {
				size_t handled = size * nmemb;
				if (results) {
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
			static string makeRequest(const string& url, const vector<string>&
				headers, const string& data = "") {
				string results;
				// first load curl enviornment (only need be called
				// once in entire session tho)
				curl_global_init(CURL_GLOBAL_ALL);
				CURL* curl = curl_easy_init(); // get a curl handle
				if (curl) {
					char error_buffer[CURL_ERROR_SIZE];
					CURLcode res;
					//setting verbose
					if (0) {
						res = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
						if (res != CURLE_OK)
							throw "curl_easy_setopt failed";
					}
					// setting error buffer
					res = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";

					// set the URL to GET from
					res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";
					//pass pointer to callback function
					res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &results);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";
					//sends all data to this function
					res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunction);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";
					// need this to catch http errors
					res = curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";
					if (data.length() > 0) {
						// Now specify the POST data
						res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
						if (res != CURLE_OK)
							throw "curl_easy_setopt failed";
						// Now specify the POST data size
						res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
						if (res != CURLE_OK)
							throw "curl_easy_setopt failed";
						//  a post request
						res = curl_easy_setopt(curl, CURLOPT_POST, 1L);
						if (res != CURLE_OK)
							throw "curl_easy_setopt failed";
					}

					struct curl_slist* curlHeaders = nullptr;
					for (const string& header : headers) {
						curlHeaders = curl_slist_append(curlHeaders, header.c_str());
					}
					res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";

					// Perform the request, res will get the return code
					res = curl_easy_perform(curl);

					if (res != CURLE_OK) {
						throw "curl_easy_perform() failed.\nCurl Error Code "
						+ to_string(res) + "\n" + curl_easy_strerror(res) +
						"\n"
						+ error_buffer + "\nPossibly Bad BRIDGES Credentials\n";
					}
					curl_slist_free_all(curlHeaders);
					curl_easy_cleanup(curl);
				}
				else {
					throw "curl_easy_init() failed!\nNothing retrieved from server.\n";
				}

				curl_global_cleanup();
				return results;
			}
	}; //server comm


}// namespace bridges
#endif
