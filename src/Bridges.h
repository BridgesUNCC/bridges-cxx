#ifndef BRIDGES_H
#define BRIDGES_H

#include <iostream>
#include <algorithm>
using namespace std;

#include "DataStructure.h" //string, using std
#include "ServerComm.h" //vector

#include <JSONutil.h>
#include <alltypes.h>

namespace bridges {
	/**
	 * @brief This class contains methods to connect and transmit a user's
	 *  data structure representation to the Bridges server (up to 5000 elements)
	 *
	 * @author Kalpathi Subramanian, Dakota Carmer
	 * @date  7/26/15, 6/5/17, 10/30/18
	 */
	class Bridges {
		private:

			static string getDefaultServerURL() {
				return "http://bridges-cs.herokuapp.com";
			}

			bool jsonFlag = false;   				// if JSON is to be printed

			string user_name = string(),
				   api_key = string(); 				// user credentials

			string description = string();			// visualization description

			string title = string();							// title of visualization

			unsigned int assn_num = 0;				// assignment id

			DataStructure* ds_handle = nullptr;  	// data structure handle

			string server_url = "http://bridges-cs.herokuapp.com";

			string BASE_URL = server_url + "/assignments/";

			// map overlay options
			string map_overlay_options[3] = {"cartesian", "albersusa", "equirectangular"};
			bool map_overlay = false;
			string coord_system_type = "cartesian";

			// world coordinate window
			vector<double> wc_window;

			unsigned int lastAssignNum = 0, subAssignNum = 0;


		public:
			Bridges() {
				Bridges (0, "", "");
			}
			Bridges (const string& name, const string& key) {
				Bridges (0, name, key);
			}

			Bridges (const unsigned int& num, const string& name, const string& key) {
				assn_num = num;
				user_name = name;
				api_key = key;
			}

			/**
			 *
			 *	@return flag indicating if JSON should be printed upon visualization
			 *
			 */
			bool getVisualizeJSONFlag() const {
				return jsonFlag;
			}

			/**
			 *
			 *	@param flag indicating if JSON should be printed upon visualization
			 *
			 */
			void setVisualizeJSONFlag(bool flag) {
				jsonFlag = flag;
			}

			/**
			 *
			 *	@return reference to member holding the BRIDGES username credential
			 *			for the server
			 *
			 */
			const string& getUserName() const {
				return user_name;
			}
			/**
			 *
			 *	@param  user_name   BRIDGES user id to set
			 *
			 */
			void setUserName(const string& name) {
				user_name = name;
			}
			/**
			 *
			 *	@return BRIDGES api key credential for the server
			 *
			 */
			const string& getApiKey()  const {
				return api_key;
			}
			/**
			 *	@param key API key to set for user
			 */
			void setApiKey(const string& key) {
				api_key = key;
			}
			/**
			 *
			 *	@return assignment number for holding the visualization on the server
			 *
			 */
			unsigned int getAssignment() const {
				return assn_num;
			}
			/**
			 *
			 *	@param assn sets the assignment number
			 *
			 */
			void setAssignment(unsigned int num) {
				assn_num =  num;

				if (assn_num != lastAssignNum) { 		// reset if a new assignment
					lastAssignNum = assn_num;
					subAssignNum = 0;
				}
			}
			/**
			 *
			 *	@return title of visualization
			 *
			 */

			const string& getTitle() const {
				return title;
			}

			/**
			 *
			 *	Set  title of visualization
			 *
			 *  @param t  title of visualization
			 *
			 */
			void setTitle(const string& t) {
				title = t;
			}
			/**
			 *	@return description of visualization
			 */

			const string& getDescription() const {
				return description;
			}
			/**
			 *	@return descr description of visualization
			 */
			void setDescription(const string& descr) {
				description = descr;
			}

			/**
			 *
			 *  set handle to data structure
			 *
			 *  @param ds pointer to user's data Structure
			 *
			 */
			void setDataStructure(DataStructure *ds) {
				ds_handle = ds;
			}

			/**
			 *
			 *  set handle to data structure
			 *
			 *  @param ds reference to user's data Structure
			 *
			 */
			void setDataStructure(DataStructure &ds) {
			  setDataStructure(&ds);
			}

			
			/**
			 *
			 *  @return member holding the data structure handle
			 *
			 */
			DataStructure* getDataStructure() {
				return ds_handle;
			}

			/**
			 * Sets Bridges assignment to "num", api key to "api" and username
			 *	to "name".
			 *
			 * @param num  The assignment number
			 * @param api The API key
			 * @param user The username
			 */
			void initialize(const unsigned int& num, const string& name, const string& key) {
				assn_num = num;
				user_name = name;
				api_key = key;
			}
			/**
			 *
			 *  @param  server server to which to connect.
			 *      Options are: ['live', 'local', 'clone'], and 'live' is the default;
			 *
			 */
			void setServer(const string& server_type) {
				if (server_type == "live")
					server_url = "http://bridges-cs.herokuapp.com";
				else if (server_type == "clone")
					server_url = "http://bridges-clone.herokuapp.com";
				else if (server_type == "local")
					server_url = "http://127.0.0.1:3000";

				BASE_URL = server_url + "/assignments/";
			}

			/**
			 *	Turns on map overlay for subsequent visualizations - used with location specific
			 *	datasets
			 *
			 *  @param flag   this is the boolean flag for displaying a map overlay
			 *
			 **/
			void setMapOverlay (bool overlay_flag) {
				map_overlay = overlay_flag;
			}

			/**
			 *  Sets the coordinate system type for location specific data; default is cartesian
			 *
			 *	@param coord    this is the desired coordinate space argument
			 *		Options are: ['cartesian', 'albersusa', 'equirectangular', 'window']. 
		     *		'cartesian' is the default
			 *
			 **/
			void setCoordSystemType (string coord) {
				std::transform(coord.begin(), coord.end(), coord.begin(), ::tolower);
				if (coord == "cartesian" || coord == "albersusa" || coord == "equirectangular"
						|| coord == "window")
					coord_system_type = coord;
				else  {
					cout << "Unrecognized coordinate system \'" + coord + "\', defaulting to "
						<< "cartesian. Options:";
					for (auto proj : map_overlay_options)
						cout <<  + "\t" ;
					coord_system_type = "cartesian";
				}
			}
			/**
			 *  Gets the coordinate system type for location specific datasets
			 *
			 *	@return coord system type ; will be one of
			 *	['cartesian', 'albersUsa', 'equirectangular']. 'cartesian'
			 *
			 **/
			const string&  getCoordSystemType () {
				return coord_system_type;
			}

			/**
			 *  sets the world coordinate window defining the space of the user
			 *	defined objects (or nodes)
			 *
			 *  @param xmin   minimum window x
			 *  @param ymin   minimum window y
			 *  @param xmax   maximum window x
			 *  @param ymax   maximum window y
			 *
			 *  @return none
			 **/
			void setWindow (int xmin, int ymin, int xmax, int ymax) {
				setWindow(double(xmin), double(ymin), double(xmax), double(ymax));
			}

			void setWindow (double xmin, double ymin, double xmax, double ymax) {
				wc_window.push_back(xmin);
				wc_window.push_back(ymin);
				wc_window.push_back(xmax);
				wc_window.push_back(ymax);
			}

			/**
			 *
			 * 	Sends relevant meta-data and representation of the data structure to the BRIDGES server,
			 *	and upon successful completion, prints the URL to display the Bridges visualization.
			 *
			 */
			void visualize() {

				if (assn_num != lastAssignNum) { 		// reset if a new assignment
					lastAssignNum = assn_num;
					subAssignNum = 0;
				}
				if (subAssignNum == 99) {
					cout << "#sub-assignments limit(99) exceeded, visualization not generated .."
						<< endl;
					return;
				}
				if (!ds_handle) {
					cerr << "Error: Data Structure handle null! Visualization not generated.";
					return;
				}

				//
				// get the JSON of the data structure
				// each data structure is responsible for generating its JSON
				//

				string ds_json = getJSONHeader() + ds_handle->getDataStructureRepresentation();

				//
				// print JSON if flag is on
				//
				if (getVisualizeJSONFlag()) {
					cout << "JSON[" + ds_handle->getDStype() + "]:\t" << ds_json << endl;
				}

				try {						// send the JSON of assignment to the server
					ServerComm::makeRequest(BASE_URL + to_string(assn_num) + "." +
						(subAssignNum > 9 ? "" : "0") + to_string(subAssignNum) + "?apikey=" + api_key +
						"&username=" + user_name, {"Content-Type: text/plain"}, ds_json);

					cout << "Success: Assignment posted to the server. " << endl <<
						"Check out your visualization at:" << endl << endl
						<< BASE_URL + to_string(assn_num) + "/" + user_name << endl << endl;
					subAssignNum++;
				}
				catch (const string& error_str) {
					cerr << "\nPosting assignment to the server failed!" << endl
						<< error_str << endl << endl;
					cerr << "Provided Bridges Credentials:" << endl <<
						"\t User Name: " << user_name << endl <<
						"\t API Key: " << api_key << endl <<
						"\t Assignment Number: " << assn_num << endl;
				}
			}

		private:
			string getServerURL() const {
				return server_url;
			}


			string getJSONHeader () {
				using bridges::JSONUtil::JSONencode;

				string json_header = OPEN_CURLY +
					QUOTE + "visual" + QUOTE + COLON + JSONencode(ds_handle->getDStype()) + COMMA +
					QUOTE + "title" + QUOTE + COLON + JSONencode(getTitle()) + COMMA +
					QUOTE + "description" + QUOTE + COLON + JSONencode( getDescription()) + COMMA +
					QUOTE + "map_overlay" + QUOTE + COLON + ((map_overlay) ? "true" : "false") + COMMA +
					QUOTE + "coord_system_type" + QUOTE + COLON + JSONencode(getCoordSystemType()) +
					COMMA;

					if (wc_window.size() == 4) {		// world coord window has been specified
						json_header += QUOTE + string("window") + QUOTE + COLON + OPEN_BOX;
						json_header += std::to_string(wc_window[0]) + COMMA + 
								std::to_string(wc_window[1]) + COMMA + 
								std::to_string(wc_window[2]) + COMMA + std::to_string(wc_window[3]);
						json_header += CLOSE_BOX + COMMA;

					}

				return json_header;
			}

			friend DataSource;
	};	//end of class Bridges

}	// end of bridges namespace
#endif
