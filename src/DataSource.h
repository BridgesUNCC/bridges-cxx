#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#include <JSONutil.h>
#include "./data_src/EarthquakeUSGS.h"
#include "./data_src/Game.h"
#include "./data_src/Shakespeare.h"
#include "./data_src/GutenbergBook.h"
#include "./data_src/CancerIncidence.h"
#include "./data_src/ActorMovieIMDB.h"
#include "./data_src/Song.h"
#include "./data_src/OSMData.h"
#include "./data_src/OSMVertex.h"
#include "./data_src/OSMEdge.h"
#include "ColorGrid.h"
#include "base64.h"
#include <GraphAdjList.h>
#include "rapidjson/document.h"
#include "assert.h"
#include "rapidjson/error/en.h"

namespace bridges {
	/**
	 * @brief This provides an API to various data sources used in BRIDGES.
	 *
	 * BRIDGES currently supports a few external datasets for use with BRIDGES
	 * assignments: USGIS Earthquake Tweeet streaming data feed, IMDB (file),
	 * Book metadata collection, IGN Game Data, Shakespear book/poem meta data.

	 * Functions are provided that access a user specified number of data
	 * records; objects of the appropriate type are returned as a list.
	 *
	 */

	class DataSource {
			int debug() const {
				return 0;
			}
			bridges::Bridges* bridges_inst;
		public:
			DataSource(bridges::Bridges* br = nullptr)
				: bridges_inst(br) {}

			DataSource(bridges::Bridges& br )
				: bridges_inst(&br) {}

			
			/**
			 *
			 *  Get meta data of the IGN games collection.
			 *
			 *  This function retrieves  and formats the data into a list of
			 *  Game objects
			 *
			 *  @throws Exception if the request fails
			 *
			 *  @return a list of Game objects,
			 *
			 */
			vector<Game> getGameData() {
				using namespace rapidjson;
				Document d;

				// request the game dataset and parse it
				d.Parse(
					ServerComm::makeRequest("http://bridgesdata.herokuapp.com/api/games",
				{"Accept: application/json"}).c_str());

				const Value& D = d["data"];
				vector<Game> wrapper;
				for (SizeType i = 0; i < D.Size(); i++) {
					const Value& V = D[i];
					const Value& G = V["genre"];

					vector<string> genre;
					for (SizeType j = 0; j < G.Size(); j++) {
						genre.push_back(G[j].GetString());
					}
					wrapper.push_back(
						Game(	V["game"].GetString(),
							V["platform"].GetString(),
							V["rating"].GetDouble(),
							genre ) );
				}
				return wrapper;
			}
			/**
			 *  Get ActorMovie IMDB Data
			 *  retrieved, formatted into a list of ActorMovieIMDB objects
			 *
			 *  @param number the number of actor/movie pairs, but currently unused,
			 *      returns all records.
			 *  @throws Exception if the request fails
			 *
			 *  @return a list of ActorMovieIMDB objects, but only actor and
			 *			movie fields in this version
			 */
			vector<ActorMovieIMDB> getActorMovieIMDBData(int number = 0) {
				using namespace rapidjson;
				Document d;
				vector<ActorMovieIMDB> wrapper;
				string url = "http://bridgesdata.herokuapp.com/api/imdb?limit=" +
					to_string(number);

				// retrieve the data and parse
				d.Parse(ServerComm::makeRequest( url, {"Accept: application/json"}).c_str());

				const Value& D = d["data"];
				for (SizeType i = 0; i < D.Size(); i++) {
					const Value& V = D[i];
					wrapper.push_back(
						ActorMovieIMDB(
							V["actor"].GetString(),
							V["movie"].GetString()
						)
					);
				}
				return wrapper;
			}


			/**
			 *  Get ActorMovie IMDB Data
			 *  retrieved, formatted into a list of ActorMovieIMDB objects
			 *
			 *  @throws Exception if the request fails
			 *
			 *  @return a list of ActorMovieIMDB objects, consisting of
			 *	actor name, movie name, movie genre and movie rating is returned.
			 *
			 */
			vector<ActorMovieIMDB> getActorMovieIMDBData2() {
				using namespace rapidjson;
				Document d;
				vector<ActorMovieIMDB> wrapper;
				string url = "https://bridgesdata.herokuapp.com/api/imdb2";

				// retrieve the data and parse
				d.Parse(ServerComm::makeRequest( url, {"Accept: application/json"}).c_str());

				const Value& D = d["data"];
				for (SizeType i = 0; i < D.Size(); i++) {
					const Value& V = D[i];
					string actor = V["actor"].GetString();
					string movie = V["movie"].GetString();
					double rating = V["rating"].GetDouble();
					const Value& G = V["genres"];
					vector<string> genres;
					for (SizeType j = 0; j < G.Size(); j++) {
						genres.push_back(G[j].GetString());
					}
					wrapper.push_back(ActorMovieIMDB( actor, movie, (float)rating, genres));
				}
				return wrapper;
			}

			/**
			 *  Get USGS earthquake data
			 *  USGS Tweet data (https://earthquake.usgs.gov/earthquakes/map/)
			 *  retrieved, formatted into a list of EarthquakeUSGS objects
			 *
			 *  @param number the number of earthquake records retrieved,
			 *		limited to 5000
			 *  @throws Exception if the request fails
			 *
			 *  @return a list of earthquake records
			 */
			vector<EarthquakeUSGS> getEarthquakeUSGSData(int number = 0) {
				using namespace rapidjson;
				Document d;
				vector<EarthquakeUSGS> wrapper;
				if (number <= 0) {
					d.Parse(ServerComm::makeRequest( "http://earthquakes-uncc.herokuapp.com/eq",
					{"Accept: application/json"}).c_str());
					for (SizeType i = 0; i < d.Size(); i++) {
						const Value& V = d[i]["properties"];
						const Value& G = d[i]["geometry"]["coordinates"];
						wrapper.push_back(
							EarthquakeUSGS(
								V["mag"].GetDouble(),
								G[0].GetDouble(),
								G[1].GetDouble(),
								V["place"].GetString(),
								V["title"].GetString(),
								V["url"].GetString(),
								V["time"].GetString() )
						);
					}
				}
				else {
					d.Parse(ServerComm::makeRequest( "http://earthquakes-uncc.herokuapp.com/eq/latest/" +
							to_string(number), {"Accept: application/json"}).c_str());

					const Value& D = d["Earthquakes"];
					for (SizeType i = 0; i < D.Size(); i++) {
						const Value& V = D[i]["properties"];
						const Value& G = D[i]["geometry"]["coordinates"];
						//				wrapper.push_back({V["mag"].GetDouble(),G[0].GetDouble(),G[1].GetDouble(),V["place"].GetString(),V["title"].GetString(),V["url"].GetString(),V["time"].GetString()});
						wrapper.push_back(
							EarthquakeUSGS(
								V["mag"].GetDouble(),
								G[0].GetDouble(),
								G[1].GetDouble(),
								V["place"].GetString(),
								V["title"].GetString(),
								V["url"].GetString(),
								V["time"].GetString() )
						);
					}
				}
				return wrapper;
			}
			/**
			 *
			 *  Get data of Shakespeare works (plays, poems)
			 *
			 *  This function retrieves  and formats the data into a
			 *  a list of Shakespeare objects.
			 *
			 *	Valid endpoints: 'poems','plays', <title>
			 *	Valid queryParams: format{simple}
			 *
			 *  @throws Exception if the request fails
			 *
			 *  @param endpoint  can be either "plays" or "poems". If this is
			 *		specified, then only these types of works are retrieved.
			 *  @param textOnly  if this is set, then only the text is retrieved.
			 *
			 *  @return an array of Shakespeare objects
			 *
			 */
			vector<Shakespeare> getShakespeareData(string endpoint = "",
				bool textonly = false) {
				using namespace rapidjson;
				Document d;
				vector<Shakespeare> wrapper;

				string url = "http://bridgesdata.herokuapp.com/api/shakespeare/";

				if (endpoint == "plays" || endpoint == "poems")
					url += "/" + endpoint;
				if (textonly) {
					url += "?format=simple";
				}
				// retrieve the data and parse
				d.Parse(ServerComm::makeRequest( url, {"Accept: application/json"}).c_str());

				const Value& D = d["data"];
				for (SizeType i = 0; i < D.Size(); i++) {
					const Value& V = D[i];
					wrapper.push_back(
						Shakespeare(
							V["title"].GetString(),
							V["type"].GetString(),
							V["text"].GetString()
						)
					);

				}
				return wrapper;
			}
			/**
			 *
			 *  Get data of a particular songs (including lyrics) using the Genius API
			 *  (https://docs.genius.com/), given the song title and artist name.
			 *	Valid endpoints:  http://bridgesdata.herokuapp.com/api/songs/find/
			 *	Valid queryParams: song title, artist name
			 *
			 *  This function retrieves  and formats the data into a
			 *  Song object. The song if not cached in the local DB is queried
			 *  and added to the DB
			 *
			 *  @throws Exception if the request fails
			 *
			 *  @return a Song object,
			 *
			 */
			Song getSong(string songTitle, string artistName) {
				using namespace rapidjson;

				Document d;
				vector<Song> wrapper;
				string url = "http://bridgesdata.herokuapp.com/api/songs/find/";
				// retrieve the data and parse
				if (songTitle.size() > 0)
					url += songTitle;
				else {
					throw "Incorrect use of getSong. songTitle should be given.";
				}

				if (artistName.size())
					url += "?artistName=" + artistName;
				else {
					throw "Incorrect use of getSong. artistName should be given.";
				}
				// check for spaces in url and replace them by '%20'
				string::size_type n = 0;
				while ( (n = url.find(" ", n)) != string::npos) {
					url.replace(n, 1, "%20");
					n++;
				}

				d.Parse(ServerComm::makeRequest( url, {"Accept: application/json"}).c_str());

				string artist 	= (d.HasMember("artist")) ?
					d["artist"].GetString() : string();
				string song 	= (d.HasMember("song"))	?
					d["song"].GetString() : string();
				string album 	= (d.HasMember("album"))	?
					d["album"].GetString() : string();
				string lyrics 	= (d.HasMember("lyrics")) ?
					d["lyrics"].GetString() : string();
				string release_date = (d.HasMember("release_date")) ?
					d["release_date"].GetString() : string();

				return Song (artist, song, album, lyrics, release_date);
			}
			/**
			 *
			 *  Get data of the songs (including lyrics) using the Genius API
			 *  https://docs.genius.com/
			 *	Valid endpoints:  https://bridgesdata.herokuapp.com/api/songs/
			 *
			 *  This function retrieves  and formats the data into a list of
			 *  Song objects. This version of the API retrieves all the cached
			 *  songs in the local DB.
			 *
			 *  @throws Exception if the request fails
			 *
			 *  @return a list of Song objects,
			 *
			 */
			vector<Song> getSongData() {
				using namespace rapidjson;

				Document d;
				vector<Song> all_songs;

				string url = "http://bridgesdata.herokuapp.com/api/songs/";
				// retrieve the data and parse

				d.Parse(ServerComm::makeRequest( url, {"Accept: application/json"}).c_str());

				const Value& D = d["data"];

				// get the songs and put them into a vector
				for (SizeType i = 0; i < D.Size(); i++) {
					const Value& v = D[i];

					//cout << v["artist"].GetString() << endl;
					string artist 	= (v.HasMember("artist")) ? v["artist"].GetString() : string();
					string song 	= (v.HasMember("song"))	? v["song"].GetString() : string();
					string album 	= (v.HasMember("album"))	? v["album"].GetString() : string();
					string lyrics 	= (v.HasMember("lyrics")) ? v["lyrics"].GetString() : string();
					string release_date = (v.HasMember("release_date")) ?
						v["release_date"].GetString() : string();
					all_songs.push_back( Song ( artist, song, album, lyrics, release_date) );

				}
				return all_songs;
			}
			/**
			 *
			 *  Get meta data of the Gutenberg book collection (1000 books)
			 *  This function retrieves,  and formats the data into a list of
			 *  GutenbergBook objects
			 *
			 *  @throws Exception if the request fails
			 *
			 *  @return a list of GutenbergBook objects,
			 *
			 */
			vector<GutenbergBook> getGutenbergBookData(int num = 0) {
				using namespace rapidjson;

				Document d;
				vector<GutenbergBook> wrapper;
				string url = "http://bridgesdata.herokuapp.com/api/books";
				if (num > 0) {
					url += "?limit=" + to_string(num);
				}

				d.Parse(ServerComm::makeRequest( url, {"Accept: application/json"}).c_str());
				const Value& D = d["data"];
				for (SizeType i = 0; i < D.Size(); i++) {
					const Value& V = D[i];

					const Value& A = V["author"];
					const Value& L = V["languages"];

					vector<string> lang;
					for (SizeType j = 0; j < L.Size(); j++) {
						lang.push_back(L[j].GetString());
					}

					const Value& G = V["genres"];
					vector<string> genre;
					for (SizeType j = 0; j < G.Size(); j++) {
						genre.push_back(G[j].GetString());
					}

					const Value& S = V["subjects"];
					vector<string> subject;
					for (SizeType j = 0; j < S.Size(); j++) {
						subject.push_back(S[j].GetString());
					}

					const Value& M = V["metrics"];
					wrapper.push_back(
						GutenbergBook(
							A["name"].GetString(),
							A["birth"].GetInt(),
							A["death"].GetInt(),
							V["title"].GetString(),
							lang,
							genre,
							subject,
							M["characters"].GetInt(),
							M["words"].GetInt(),
							M["sentences"].GetInt(),
							M["difficultWords"].GetInt(),
							V["url"].GetString(),
							V["downloads"].GetInt()
						)
					);
				}
				return wrapper;
			}
			/*
			 * Retrieves the CDC dataset into a vector of records
			 * See CancerIncidence class for more information
			 *
			 */
			vector<CancerIncidence> getCancerIncidenceData(int num = 0) {
				using namespace rapidjson;

				Document d;
				vector<CancerIncidence> wrapper;
				string url = "https://bridgesdata.herokuapp.com/api/cancer/withlocations";
				if (num > 0) {
					url += "?limit=" + to_string(num);
				}

				d.Parse(ServerComm::makeRequest( url, {"Accept: application/json"}).c_str());

				// get the JSON dataset
				const Value& D = d["data"];

				CancerIncidence c;
				for (SizeType i = 0; i < D.Size(); i++) {
					const Value& v = D[i];
					const Value& age = v["Age"];

					c.setAgeAdjustedRate( age["Age Adjusted Rate"].GetDouble());
					c.setAgeAdjustedCI_Lower(age["Age Adjusted CI Lower"].GetDouble());
					c.setAgeAdjustedCI_Upper(age["Age Adjusted CI Upper"].GetDouble());

					c.setYear(v["Year"].GetInt());

					const Value& data = v["Data"];
					c.setCrudeRate(data["Crude Rate"].GetDouble());
					c.setCrudeRate_CI_Lower(data["Crude CI Lower"].GetDouble());
					c.setCrudeRate_CI_Upper(data["Crude CI Upper"].GetDouble());
					c.setRace(data["Race"].GetString());
					c.setPopulation(data["Population"].GetInt());
					c.setEventType(data["Event Type"].GetString());

					c.setAffectedArea(v["Area"].GetString());

					const Value& loc = v["loc"];
					c.setLocationX(loc[0].GetDouble());
					c.setLocationY(loc[1].GetDouble());

					wrapper.push_back(c);
				}
				return wrapper;
			}
			OSMData *getOSMData (string location) {
				using namespace rapidjson;

				Document osm_data;
				std::transform(location.begin(), location.end(), location.begin(), 
													::tolower);
				string url = string("http://osm-api.herokuapp.com/name/") + location;
				cout << "url(before):" << url << endl;

								// get the OSM data json
				string osm_json = ServerComm::makeRequest(url, {"Accept: application/json"});

				cout << osm_json <<endl;
								// parse the json
//				if (osm_data.Parse(osm_json.c_str()).HasParseError()) {
//					cout << "\nError(offset " <<  (unsigned)osm_data.GetErrorOffset() << 
//       				GetParseError_En(osm_data.GetParseError());
//					cout << "Aha! Parse error!" << endl;
//				}
				osm_data.Parse<ParseFlag::kParseStopWhenDoneFlag>(osm_json.c_str());

				

								// create an osm data object
				OSMData *osm = new OSMData;

				unordered_map<long, int> vert_map; // to remap the vertex ids

				if (osm_data.HasMember("nodes")) {
					vector<OSMVertex> vertices;
					Value& nodes = osm_data["nodes"];

					vector<long> vertex_ids;
														// get the vertices
					for (SizeType i = 0; i < nodes.Size(); i++) {
						const Value& node = nodes[i];
						long id = node[0].GetInt64();
										// map vertex ids to 0...maxVert range
						vert_map[id] = i;
						vertex_ids.push_back(id);
						double lat = node[1].GetDouble(), longit = node[2].GetDouble();
						vertices.push_back(OSMVertex(lat, longit));
						cout<< i << ":" << id << "," << lat  << "," << longit << endl;
					}
					osm->setVertices(vertices);
				}
										// add vertices to object
										// get the edges

				if (osm_data.HasMember("edges")) {
					vector<OSMEdge> edges;
					Value& links = osm_data["edges"];

					for (SizeType i = 0; i < links.Size(); i++) {
						const Value& link = links[i];
						long id1 = link[0].GetInt64();
						long id2 = link[1].GetInt64();
						double dist = link[2].GetDouble();

						cout<< i << ":" << vert_map[id1] << "," << vert_map[id2]  << "," << dist<< endl;

						edges.push_back(OSMEdge(vert_map[id1], vert_map[id2], dist));
					}
					osm->setEdges(edges);
				}
										// add edges to object
	
				if (osm_data.HasMember("meta")) {
										// get lat long range
					Value& meta = osm_data["meta"];
					double lat_min = meta["lat_min"].GetDouble();
					double lat_max = meta["lat_max"].GetDouble();
					double longit_min = meta["lon_min"].GetDouble();
					double longit_max = meta["lon_max"].GetDouble();
					cout << lat_min << "," << lat_max << "," << longit_min << "," << longit_max << endl;
					osm->setLatLongRange(lat_min, lat_max, longit_min, longit_max);
										// get dataset name
					osm->setName(meta["name"].GetString());
					cout << osm->getName() << endl;
				}
				return osm;
			}

//			GraphAdjList  getOSMDataAsGraph (string location, double latitudeMin, 
//					double longitutdeMin, double longitMax, double longitutdeMax) {
//			}

			/**Reconstruct a GraphAdjList from an existing GraphAdjList on the Bridges server
			 *
			 * The reconstructed assignment sees vertices identified as integers in the order they are stored in the server.
			 * The data associated with a vertex is a string that come from the label of that vertices.
			 * The data associated with an edge is the string that come from the label of that edge.
			 * The edge weights are also reobtained from the bridges server.
			 *
			 * @return the ColorGrid stored in the bridges server
			 * @param user the name of the user who uploaded the assignment
			 * @param assignment the ID of the assignment to get
			 * @param subassignment the ID of the subassignment to get
			 **/
			bridges::GraphAdjList<int, std::string> getGraphFromAssignment (const std::string& user,
				int assignment,
				int subassignment = 0) {
				bridges::GraphAdjList<int, std::string> gr;

				std::string s = this->getAssignment(user, assignment, subassignment);

				rapidjson::Document doc;
				doc.Parse(s.c_str());
				if (doc.HasParseError())
					throw "Malformed JSON";

				//Access doc["assignmentJSON"]
				const auto& assjson = doc.FindMember("assignmentJSON");

				if (assjson == doc.MemberEnd())
					throw "Malformed GraphAdjacencyList JSON: no assignmentJSON";

				//Access doc["assignmentJSON"]["data"]
				const auto& dataArray = assjson->value.FindMember("data");

				if (dataArray == assjson->value.MemberEnd()
					|| dataArray->value.IsArray() == false)
					throw "Malformed GraphAdjacencyList JSON: No data";

				const auto& data = dataArray->value.GetArray()[0];

				//Access doc["assignmentJSON"]["data"][0]["visual"]
				const auto& dataVisual = data.FindMember("visual");

				if (dataVisual == data.MemberEnd() ||
					dataVisual->value.IsString() == false)
					throw "Malformed GraphAdjacencyList JSON";

				std::string assignment_type = dataVisual->value.GetString();

				if (assignment_type != "GraphAdjacencyList")
					throw "Malformed GraphAdjacencyList JSON: Not a GraphAdjacencyList";

				//reconstructing vertices out of nodes, and using the optional "name" as the data associated
				{
					const auto& nodes = data.FindMember("nodes");
					if (nodes == data.MemberEnd() ||
						nodes->value.IsArray() == false)
						throw "Malformed GraphAdjacencyList JSON: malformed nodes";


					const auto& nodeArray = nodes->value.GetArray();
					int nbVertex = nodeArray.Size();
					for (int i = 0; i < nbVertex; ++i) {
						std::string name;

						const auto& vertexJSONstr = nodeArray[i];

						const auto& nameJSON = vertexJSONstr.FindMember("name");
						if (nameJSON != vertexJSONstr.MemberEnd()
							&& nameJSON->value.IsString()) {
							name = nameJSON->value.GetString();
						}
						gr.addVertex(i, name);
					}
				}

				//reconstructing links, and using "label" as data associated with the link
				{
					const auto& links = data.FindMember("links");
					if (links == data.MemberEnd() ||
						links->value.IsArray() == false)
						throw "Malformed GraphAdjacencyList JSON: malformed links";

					const auto& linkArray = links->value.GetArray();
					int nbLink = linkArray.Size();
					for (int i = 0; i < nbLink; ++i) {
						std::string name;
						int src;
						int dest;
						int wgt;

						const auto& linkJSONstr = linkArray[i];

						//checking label. Maybe does not exist? (is that field optional?)
						const auto& nameJSON = linkJSONstr.FindMember("label");
						if (nameJSON != linkJSONstr.MemberEnd()
							&& nameJSON->value.IsString()) {
							name = nameJSON->value.GetString();
						}

						//checking source
						const auto& srcJSON = linkJSONstr.FindMember("source");
						if (srcJSON == linkJSONstr.MemberEnd()
							|| srcJSON->value.IsInt() == false) {
							throw "Malformed GraphAdjacencyList JSON: malformed link";
						}
						src = srcJSON->value.GetInt();


						//checking destination
						const auto& dstJSON = linkJSONstr.FindMember("target");
						if (dstJSON == linkJSONstr.MemberEnd()
							|| dstJSON->value.IsInt() == false) {
							throw "Malformed GraphAdjacencyList JSON: malformed link";
						}
						dest = dstJSON->value.GetInt();

						//checking weight. //why is weight a mandatory parameter?
						const auto& wgtJSON = linkJSONstr.FindMember("weight");
						if (wgtJSON == linkJSONstr.MemberEnd()
							|| wgtJSON->value.IsInt() == false) {
							throw "Malformed GraphAdjacencyList JSON: malformed link";
						}
						wgt = wgtJSON->value.GetInt();


						//adding edge.
						gr.addEdge(src, dest, wgt, name);
					}
				}

				return gr;
			}

			/**Reconstruct a ColorGrid from an existing ColorGrid on the Bridges server
			 *
			 * @return the ColorGrid stored in the bridges server
			 * @param user the name of the user who uploaded the assignment
			 * @param assignment the ID of the assignment to get
			 * @param subassignment the ID of the subassignment to get
			 **/
			bridges::ColorGrid getColorGridFromAssignment(const std::string& user,
				int assignment,
				int subassignment = 0) {

				std::string s = this->getAssignment(user, assignment, subassignment);

				rapidjson::Document doc;
				doc.Parse(s.c_str());
				if (doc.HasParseError())
					throw "Malformed JSON";

				try {
					std::string assignment_type = doc["assignment_type"].GetString();

					if (assignment_type != "ColorGrid")
						throw "Malformed ColorGrid JSON: Not a ColorGrid";
				}
				catch (rapidjson_exception re) {
					throw "Malformed JSON: Not a Bridges assignment?";
				}


				try {
					auto& data = doc["data"][0];

					std::string encoding = data["encoding"].GetString();
					if (encoding != "RAW" && encoding != "RLE")
						throw "Malformed ColorGrid JSON: encoding not supported";


					//Access doc["data"][0]["dimensions"]
					const auto& dimensions = data["dimensions"];
					int dimx = dimensions[0].GetInt();
					int dimy = dimensions[1].GetInt();

					if (debug())
						std::cerr << "Dimensions: " << dimx << "x" << dimy << std::endl;

					//Access doc["data"][0]["nodes"][0]
					std::string base64_encoded_assignment = data["nodes"][0].GetString();


					std::vector<bridges::BYTE> decoded = bridges::base64::decode(base64_encoded_assignment);

					bridges::ColorGrid cg (dimx, dimy);


					if (encoding == "RAW") {
						if (debug())
							std::cerr << "decoding RAW" << std::endl;
						if (debug())
							std::cerr << "length: " << decoded.size() << std::endl;
						if (decoded.size() < dimx * dimy * 4)
							throw "Malformed ColorGrid JSON: nodes is smaller than expected";

						//first pixel
						//std::cerr<<(int)decoded[0]<<" "<<(int)decoded[1]<<" "<<(int)decoded[2]<<" "<<(int)decoded[3]<<std::endl;

						//bridges::ColorGrid* ptr = new bridges::ColorGrid (dimx, dimy);

						size_t base = 0;

						for (int x = 0; x < dimx; ++x) {
							for (int y = 0; y < dimy; ++y) {
								bridges::Color c ((int)decoded[base],
									(int)decoded[base + 1],
									(int)decoded[base + 2],
									(int)decoded[base + 3]
								);

								cg.set(x, y, c);
								base += 4;
							}
						}
					}
					else if (encoding == "RLE") {
						if (debug())
							std::cerr << "Decoding RLE" << std::endl;

						int currentInDecoded = 0;
						int currentInCG = 0;
						while (currentInDecoded != decoded.size()) {
							if (currentInDecoded + 5 > decoded.size())
								throw "Malformed ColorGrid JSON: nodes is not a multiple of 5";



							int repeat = (BYTE) decoded[currentInDecoded++];
							int r = (BYTE) decoded[currentInDecoded++];
							int g = (BYTE) decoded[currentInDecoded++];
							int b = (BYTE) decoded[currentInDecoded++];
							int a = (BYTE) decoded[currentInDecoded++];

							if (debug())
								std::cerr << "indecoded: " << currentInDecoded
									<< " repeat: " << (int)repeat
									<< " color(" << (int)r << "," << (int)g << "," << (int)b << "," << (int)a << ")"
									<< std::endl;

							bridges::Color c (r, g, b, a);

							while (repeat >= 0) {
								int posX = currentInCG / dimy;
								int posY = currentInCG % dimy;
								if (posX >= dimx || posY >= dimy) {
									if (debug())
										std::cerr << posX << " " << dimx << " " << posY << " " << dimy << std::endl;
									throw "Malformed ColorGrid JSON: Too much data in nodes";
								}
								cg.set(posX, posY, c);

								currentInCG++;
								repeat --;
							}
						}
						if (debug())
							std::cerr << "written " << currentInCG << " pixels" << std::endl;
						if (currentInCG != dimx * dimy)
							throw "Malformed ColorGrid JSON: Not enough data in nodes";
					}

					return cg;
				}
				catch (rapidjson_exception re) {
					throw "Malformed ColorGrid JSON";
				}

			}
		private:
			/***
			 * This function obtains the JSON representation of a particular subassignment.
			 *
			 * @return a string that is the JSON representation of the subassignment as stored by the Bridges server.
			 * @param user the name of the user who uploaded the assignment
			 * @param assignment the ID of the assignment to get
			 * @param subassignment the ID of the subassignment to get
			 ***/
			std::string getAssignment(std::string user,
				int assignment,
				int subassignment = 0) {
				std::vector<std::string> headers;

				std::stringstream ss;

				///should probably get the server name from a Bridges object
				if (bridges_inst)
					ss << bridges_inst->getServerURL();
				else
					ss << bridges::Bridges::getDefaultServerURL();
				ss << "/assignmentJSON/"
					<< assignment << ".";
				ss << std::setfill('0') << std::setw(2) << subassignment;
				ss << "/" << user;

				std::string url = ss.str();

				//  std::cout<<"URL: "<<url<<std::endl;

				std::string s = bridges::ServerComm::makeRequest(url, headers);

				return s;
			}
	}; // namespace DataSource

} // namespace bridges
#endif
