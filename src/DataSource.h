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
#include "./data_src/ElevationData.h"
#include "./data_src/OSMData.h"
#include "./data_src/OSMVertex.h"
#include "./data_src/OSMEdge.h"
#include "./data_src/MovieActorWikidata.h"
#include "ColorGrid.h"
#include "base64.h"
#include <GraphAdjList.h>
#include <ServerComm.h>
#include <Bridges.h>
#include "rapidjson/document.h"
#include "assert.h"
#include "rapidjson/error/en.h"
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


#include <Cache.h>


namespace bridges {
	using namespace bridges::dataset;
	using namespace bridges::datastructure;




	/**
	 * @brief This class provides an API to various data sources used in BRIDGES.
	 *
	 * BRIDGES currently supports a few external datasets for use with BRIDGES
	 * assignments: USGIS Earthquake Tweeet streaming data feed, IMDB (file),
	 * Book metadata collection, IGN Game Data, Shakespear book/poem meta data, etc.

	 * Functions are provided that access a user specified number of data
	 * records; objects of the appropriate type are returned as a list.
	 *
	 */

	class DataSource {

		private:

			int debug() const {
				return 0;
			}
			bridges::Bridges* bridges_inst;
			bridges::lruCache my_cache;

			string getOSMBaseURL() const {
				//return "http://cci-bridges-osm-t.uncc.edu/";
				return "http://cci-bridges-osm.uncc.edu/";
			}

		public:
			DataSource(bridges::Bridges* br = nullptr)
				: bridges_inst(br), my_cache(120) {}

			DataSource(bridges::Bridges& br )
				: DataSource(&br) {}


			/**
			 *
			 *  @brief Get meta data of the IGN games collection.
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
			 *  @brief Get ActorMovie IMDB Data
			 *  Data is retrieved, formatted into a list of ActorMovieIMDB objects
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
			 *  @brief Get ActorMovie IMDB Data
			 *  Data is retrieved, formatted into a list of ActorMovieIMDB objects
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
				string url = "http://bridgesdata.herokuapp.com/api/imdb2";

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
			 *  @brief Get USGS earthquake data
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
			 *  @brief Get data of Shakespeare works (plays, poems)
			 *
			 *  This function retrieves  and formats the data into a
			 *  a list of Shakespeare objects.
			 *
			 *  @throws Exception if the request fails
			 *
			 *  @param type can be "plays", "poems", or "". If this is
			 *		specified, then only these types of works are retrieved.
			 *  @param textonly  if this is set, then only the text is retrieved. (that is to say punctuation is stripped out)
			 *
			 *  @return an array of Shakespeare objects
			 *
			 */
			vector<Shakespeare> getShakespeareData(string type = "",
				bool textonly = false) {
				using namespace rapidjson;
				Document d;
				vector<Shakespeare> wrapper;

				string url = "http://bridgesdata.herokuapp.com/api/shakespeare/";

				if (type == "plays" || type == "poems")
					url += "/" + type;
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
			 *  @brief Get data of a particular songs (including lyrics) using
			 *	 the Genius API
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
			 *  @brief Get data of the songs (including lyrics) using the Genius API
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
			 *  @brief Get meta data of the Gutenberg book collection.
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
			/**
			 * @brief Retrieves the CDC dataset of Cancer Incidence.
			 *  Data is retrieved  into a vector of records
			 * See CancerIncidence class for more information
			 *
			 */
			vector<CancerIncidence> getCancerIncidenceData(int num = 0) {
				using namespace rapidjson;

				Document d;
				vector<CancerIncidence> wrapper;
				string url = "http://bridgesdata.herokuapp.com/api/cancer/withlocations";
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
					c.setCount(data["Count"].GetInt());

					c.setAffectedArea(v["Area"].GetString());

					const Value& loc = v["loc"];
					c.setLocationX(loc[0].GetDouble());
					c.setLocationY(loc[1].GetDouble());

					wrapper.push_back(c);
				}
				return wrapper;
			}
			/**
			 *
			 * @brief Retrieves the Open Street Map data from a prebuilt JSON of OSM
			 * dataset.
			 *
			 * @param osm_json JSON string
			 */
			OSMData getOSMDataFromJSON (const string& osm_json) {
				using namespace rapidjson;

				Document osm_data;

				osm_data.Parse(osm_json.c_str());

				// create an osm data object
				OSMData osm;

				if (osm_data.HasMember("nodes")) {
					vector<OSMVertex> vertices;
					Value& nodes = osm_data["nodes"];

					vector<long> vertex_ids;
					// get the vertices
					for (SizeType i = 0; i < nodes.Size(); i++) {
						const Value& node = nodes[i];
						OSMVertex::OSMVertexID id = node[0].GetInt64();

						vertex_ids.push_back(id);
						double lat = node[1].GetDouble(), longit = node[2].GetDouble();
						vertices.push_back(OSMVertex(id, lat, longit));
					}
					osm.setVertices(vertices);
				}
				// add vertices to object
				// get the edges

				if (osm_data.HasMember("edges")) {
					vector<OSMEdge> edges;
					Value& links = osm_data["edges"];

					for (SizeType i = 0; i < links.Size(); i++) {
						const Value& link = links[i];
						OSMVertex::OSMVertexID id1 = link[0].GetInt64();
						OSMVertex::OSMVertexID id2 = link[1].GetInt64();
						double dist = link[2].GetDouble();

						edges.push_back(OSMEdge(id1, id2, dist));
					}
					osm.setEdges(edges);
				}
				// add edges to object

				if (osm_data.HasMember("meta")) {
					// get lat long range
					Value& meta = osm_data["meta"];
					double lat_min = meta["lat_min"].GetDouble();
					double lat_max = meta["lat_max"].GetDouble();
					double longit_min = meta["lon_min"].GetDouble();
					double longit_max = meta["lon_max"].GetDouble();
					osm.setLatLongRange(lat_min, lat_max, longit_min, longit_max);
					// get dataset name
					osm.setName(meta["name"].GetString());
				}
				return osm;
			}


			/**
			 *
			 *  @brief Get OpenStreetMap data given a bounding rectangle of
			 *	lat/long values.
			 *
			 *  @param lat_min  latitude minimum
			 *  @param long_min  longitude minimum
			 *  @param lat_max   latitude maximum
			 *  @param long_max   longitude maximum
			 *  @param level      data resolution
			 *  @throws Exception if the request fails
			 *
			 *  @return an OSMData object
			 *
			 */
			OSMData getOSMData (double lat_min, double long_min,
				double lat_max, double long_max, string level = "default") {

				//URL for hash request
				string hash_url = getOSMBaseURL() + "hash?minLon=" + std::to_string(long_min) +
					"&minLat=" + std::to_string(lat_min) +
					"&maxLon=" + std::to_string(long_max) +
					"&maxLat=" + std::to_string(lat_max) +
					"&level=" + ServerComm::encodeURLPart(level);

				//URL to request map
				string url =
					getOSMBaseURL() + "coords?minLon=" + std::to_string(long_min) +
					"&minLat=" + std::to_string(lat_min) +
					"&maxLon=" + std::to_string(long_max) +
					"&maxLat=" + std::to_string(lat_max) +
					"&level=" + ServerComm::encodeURLPart(level);

				//trys to get hash value for bounding box map
				if (debug())
					std::cerr << "Hitting hash URL: " << hash_url << "\n";
				string hash_value =  ServerComm::makeRequest(hash_url, {"Accept: application/json"});


				std::string osm_json;
				//std::cerr<<"url: "<<url<<"\n";

				//Checks to see if map requested is stored in local cache
				if (my_cache.inCache(hash_value) == true) { //local map is up-to-date
					try {
						if (my_cache.inCache(hash_value)) {
							osm_json = my_cache.getDoc(hash_value);
						}
					}
					catch (CacheException& ce) {
						//something went bad trying to access the cache
						std::cout << "Exception while reading from cache. Ignoring cache and continue." << std::endl;
					}

				}
				else if (hash_value.compare("false") == 0 || my_cache.inCache(hash_value) == false) {
					//Server response is false or somehow map got saved as false

					if (debug())
						std::cerr << "Hitting json URL: " << url << "\n";

					osm_json = ServerComm::makeRequest(url, {"Accept: application/json"}); //Requests the map data then requests the maps hash
					if (debug())
						std::cerr << "Hitting hash URL: " << hash_url << "\n";

					hash_value =  ServerComm::makeRequest(hash_url, {"Accept: application/json"});

					if (hash_value.compare("false") == 0) {
						std::cerr << "Error while gathering hash data for generated map..." << std::endl;
						std::cerr << osm_json << std::endl;
						abort();
					}

					//Saves map to cache directory
					try {
						my_cache.putDoc(hash_value, osm_json);

					}
					catch (CacheException& ce) {

						//something went bad trying to access the cache
						std::cerr << "Exception while storing in cache. Weird but not critical." << std::endl;
						if (debug())
							std::cerr << "Tried to store hash=" << hash_value << " key=" << osm_json << std::endl;
					}

				}
				return getOSMDataFromJSON(osm_json);
			}

	  void getAmenityData(double minLat, double minLon, double 
			      maxLat, double maxLon, std::string amenity) {
	  }

	  void getAmenityData(const std::string& location, const std::string& amenity) {
	    std::string url = getOSMBaseURL() + "amenity?location=" + location
	      + "&amenity=" + amenity;

	    std::string hash_url = getOSMBaseURL() + "hash?location=" + location
	      + "&amenity=" + amenity;
	    
	    
	  }

	  
			/**
			 *
			 *  Get OpenStreetMap data given a city name and resolution level
			 *
			 *  @param location   location name (string)
			 *  @param level      data resolution
			 *
			 *  @throws Exception if the request fails
			 *
			 *  @return an OSMData object
			 *
			 */
			OSMData getOSMData (string location, string level = "default") {
				//URL for hash request
				string hash_url = getOSMBaseURL() + "hash?location=" + ServerComm::encodeURLPart(location) +
					"&level=" + ServerComm::encodeURLPart(level);

				//URL to request map
				string url =
					getOSMBaseURL() + "loc?location=" + ServerComm::encodeURLPart(location) +
					"&level=" + ServerComm::encodeURLPart(level);

				//trys to get hash value for bounding box map
				if (debug())
					std::cerr << "Hitting hash URL: " << hash_url << "\n";
				string hash_value =  ServerComm::makeRequest(hash_url, {"Accept: application/json"});


				std::string osm_json;

				if (debug())
					std::cerr << "url: " << url << "\n";

				if (my_cache.inCache(hash_value) == true) { //local map is up-to-date
					try {
						if (my_cache.inCache(hash_value)) {
							osm_json = my_cache.getDoc(hash_value);
						}
					}
					catch (CacheException& ce) {   //something went bad trying to access the cache
						std::cout << "Exception while reading from cache. Ignoring cache and continue." << std::endl;
					}

				}
				else if (hash_value.compare("false") == 0 || my_cache.inCache(hash_value) == false) { //Server response is false or somehow map got saved as false
					if (debug())
						std::cerr << "Hitting json URL: " << url << "\n";
					osm_json = ServerComm::makeRequest(url, {"Accept: application/json"}); //Requests the map data then requests the maps hash
					if (debug())
						std::cerr << "Hitting hash URL: " << hash_url << "\n";
					hash_value =  ServerComm::makeRequest(hash_url, {"Accept: application/json"});
					if (hash_value.compare("false") == 0) {
						std::cerr << "Error while gathering hash data for generated map..." << std::endl;
						std::cerr << osm_json << std::endl;
						abort();
					}

					//Saves map to cache directory
					try {
						my_cache.putDoc(hash_value, osm_json);
					}
					catch (CacheException& ce) {
						//something went bad trying to access the cache
						std::cerr << "Exception while storing in cache. Weird but not critical." << std::endl;
						if (debug())
							std::cerr << "Tried to store hash=" << hash_value << " key=" << osm_json << std::endl;
					}

				}
				return getOSMDataFromJSON(osm_json);
			}


			/**
			 * @brief old interface for the OSM data set.
			 *
			 * This is hitting a simpler API that has only a few map in
			 * 	 there: "uncc_campus", "charlotte", "washington_dc",
			 * 	 "saint_paul", "new_york", "los_angeles",
			 * 	 "san_francisco", "miami", "minneapolis", "dallas"
			 *
			 * @param location which location to get the map from
						OSMData getOSMDataOld (string location) {
							std::transform(location.begin(), location.end(), location.begin(),
								::tolower);
							std::string osm_json;
							bool from_cache = false;
							try {
								if (my_cache.inCache(location)) {
									osm_json = my_cache.getDoc(location);
									from_cache = true;
								}
							}
							catch (CacheException& ce) {
								//something went bad trying to access the cache
								std::cout << "Exception while reading from cache. Ignoring cache and continue." << std::endl;
							}

							string url = string("http://osm-api.herokuapp.com/name/") + location;

							if (!from_cache) {
								// get the OSM data json
								osm_json = ServerComm::makeRequest(url, {"Accept: application/json"});

								try {
									my_cache.putDoc(location, osm_json);
								}
								catch (CacheException& ce) {
									//something went bad trying to access the cache
									std::cerr << "Exception while storing in cache. Weird but not critical." << std::endl;
								}
							}

							return getOSMDataFromJSON(osm_json);

						}
			*/

			/**
			 * Reconstruct a GraphAdjList from an existing GraphAdjList on the Bridges server
			 *
			 * The reconstructed assignment sees vertices identified as integers in the order they are stored in the server.
			 * The data associated with a vertex is a string that comes from the label of that vertices.
			 * The data associated with an edge is the string that comes from the label of that edge.
			 * The edge weights are also reobtained from the bridges server.
			 *
			 * @param user the name of the user who uploaded the assignment
			 * @param assignment the ID of the assignment to get
			 * @param subassignment the ID of the subassignment to get
			 *
			 * @return the ColorGrid stored in the bridges server
			 *
			 */
			bridges::GraphAdjList<int, std::string> getGraphFromAssignment (
				const std::string& user,
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
						gr.addEdge(src, dest, name);
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


			void removeFirstOccurence (std::string & str, const std::string & toRemove) {
				size_t pos = str.find(toRemove);
				if (pos  != std::string::npos) {
					str.erase(pos, toRemove.length());
				}
			}

			///@brief This function returns the Movie and Actors playing
			///in them between two years
			///
			/// Internally this function gets directly the range data
			/// from wikidata. This can cause wikidata to kick the user
			/// out or return invalid JSON if the range is too wide.
			///
			/// @param yearbegin, yearend interval of years to obtain, yearbegin and yearend are included.
			/// @param vout vector where the pairs will be aded to
			void  getWikidataActorMovieDirect (int yearbegin, int yearend, std::vector<MovieActorWikidata>& vout) {
				std::string codename = "wikidata-actormovie-" + std::to_string(yearbegin) + "-" + std::to_string(yearend);
				std::string json;
				bool from_cache = false;
				try {
					if (my_cache.inCache(codename)) {
						json = my_cache.getDoc(codename);
						from_cache = true;
					}
				}
				catch (CacheException& ce) {
					//something went bad trying to access the cache
					std::cout << "Exception while reading from cache. Ignoring cache and continue." << std::endl;
				}


				if (!from_cache) {
					std::vector<std::string> http_headers;
					http_headers.push_back("User-Agent: bridges-cxx"); //wikidata kicks you out if you don't have a useragent
					http_headers.push_back("Accept: application/json"); //tell wikidata we are OK with JSON

					string url = "https://query.wikidata.org/sparql?";

					//Q1860 is "English"
					//P364 is "original language of film or TV show"
					//P161 is "cast member"
					//P577 is "publication date"
					//A11424 is "film"
					//P31 is "instance of"
					// "instance of film" is necessary to filter out tv shows
					std::string sparqlquery = "SELECT ?movie ?movieLabel ?actor ?actorLabel WHERE \
{\
  ?movie wdt:P31 wd:Q11424.\
  ?movie wdt:P161 ?actor.\
  ?movie wdt:P364 wd:Q1860.\
  ?movie wdt:P577 ?date.\
  FILTER(YEAR(?date) >= " + std::to_string(yearbegin) + " && YEAR(?date) <= " + std::to_string(yearend) + ").\
    SERVICE wikibase:label { bd:serviceParam wikibase:language \"en\". } \
}";
					url += "query=" + ServerComm::encodeURLPart(sparqlquery);
					url += "&";
					url += "format=json";

					// get the OSM data json
					json = ServerComm::makeRequest(url, http_headers);

					try {
						my_cache.putDoc(codename, json);
					}
					catch (CacheException& ce) {
						//something went bad trying to access the cache
						std::cerr << "Exception while storing in cache. Weird but not critical." << std::endl;
					}
				}

				{
					using namespace rapidjson;
					rapidjson::Document doc;
					doc.Parse(json.c_str());
					if (doc.HasParseError())
						throw "Malformed JSON";

					try {
						const auto& resultsArray = doc["results"]["bindings"].GetArray();

						for (auto& mak_json : resultsArray) {
							MovieActorWikidata mak;

							// all wikidata uri start with "http://www.wikidata.org/entity/"
							// so strip it out because it does not help discriminate and
							// consume memory and runtime to compare string
							std::string actoruri = mak_json["actor"]["value"].GetString();
							std::string movieuri = mak_json["movie"]["value"].GetString();
							removeFirstOccurence (actoruri, "http://www.wikidata.org/entity/");

							removeFirstOccurence (movieuri, "http://www.wikidata.org/entity/");


							mak.setActorURI(actoruri);
							mak.setMovieURI(movieuri);
							mak.setActorName(mak_json["actorLabel"]["value"].GetString());
							mak.setMovieName(mak_json["movieLabel"]["value"].GetString());
							vout.push_back(mak);
						}

					}
					catch (rapidjson_exception re) {
						throw "Malformed JSON: Not from wikidata?";
					}
				}
			}
		public:

			///@brief This function returns the Movie and Actors playing
			///in them between two years.
			///
			/// Return movie pair in the [yearbegin; yearend] interval.
			///
			/// @param yearbegin first year to include
			/// @param yearend last year to include
			std::vector<MovieActorWikidata> getWikidataActorMovie (int yearbegin, int yearend) {
				//Internally this function get the data year by year. This
				//is pretty bad because it hits wikidata the first time
				//for multiple years. But it enables to work around
				//wikidata's time limit.  This also works well because the
				//Cache will store each year independently and so without
				//redundancy.  Though I (Erik) am not completely sure that a
				//movie can be appear in different years, for instance it
				//can be released in the US in 2005 but in canada in
				//2006...

				std::vector<MovieActorWikidata> ret;
				for (int y = yearbegin; y <= yearend; ++y) {
					cout << "getting year " << y << endl;
					getWikidataActorMovieDirect (y, y, ret);
				}
				return ret;
			}


			/**
			* Returns ElevationData for the provided coordinate box at the
			* given resolution. Note that the ElevationData that is returned
			* may have slightly different location and resolution.
			*
			* @param latitMin minimum latitude requested
			* @param longitMin maximum latitude requested
			* @param latitMax minimum longitude requested
			* @param longitMax maximum longitude requested
			* @param res spatial resolution, aka the distance between two samples (in degrees)
			**/
			ElevationData *getElevationData (
				double latitMin, double longitMin,
				double latitMax, double longitMax, double res = 0.0166)  {

				// set up the elevation data url to get the data, given
				// a lat/long bounding box
				string server_str =
					"http://bridges-data-server-elevation.bridgesuncc.org/";

				string elev_str = "elevation?";

				string bbox_str =
					"&minLon=" 	+ std::to_string(longitMin) +
					"&minLat=" 	+ std::to_string(latitMin) +
					"&maxLon=" + std::to_string(longitMax) +
					"&maxLat=" + std::to_string(latitMax);

				string resn_str = "&resX=" + std::to_string(res)
					+ "&resY=" + std::to_string(res);

				string elev_data_url =
					server_str + elev_str + bbox_str + resn_str;

				if (debug())
					cerr << "Hitting data URL: " << elev_data_url << "\n";
				string hash_str = "hash?";
				string hash_url = server_str + hash_str + bbox_str + resn_str;

				if (debug())
					cerr << "Hitting hash URL: " << hash_url << "\n";

				// get hash value for elevation data
				string hash_value =  ServerComm::makeRequest(hash_url,
				{"Accept: application/json"});

				string elev_json;

				//Checks to see if elevation data is already in local cache
				if (my_cache.inCache(hash_value)) { // already exists
					try {
						elev_json = my_cache.getDoc(hash_value);
					}
					catch (CacheException& ce) {
						//something went bad trying to access the cache
						cout << "Exception while reading from cache. Ignoring cache." << std::endl;
					}
				}
				else { //Server response is false or not cached

					if (debug())
						cerr << "Hitting json URL: " << elev_data_url << "\n";

					// get the eleveation data
					elev_json = ServerComm::makeRequest(elev_data_url,
										{"Accept: application/json"});

					if (debug())
						cerr << "Hitting elev data URL: " << elev_data_url << "\n";

					string hash_value =  ServerComm::makeRequest(hash_url,
										{"Accept: application/json"});

					if (hash_value != "false") {
						// store map in cache
						try {
							my_cache.putDoc(hash_value, elev_json);
						}
						catch (CacheException& ce) {
							//something went bad trying to access the cache
							cerr << "Exception while storing in cache. Weird but not critical."
								<< endl;
						}
					}
				}
				return getElevationDataFromJSON(elev_json);
			}

			// get Elevation data from the JSON
			ElevationData *getElevationDataFromJSON (string elev_json) {

				// use a string stream to parse the data, which is not really a JSON,
				// but raw text
				stringstream ss(elev_json);

				int rows, cols, elev_val;
				double ll_x, ll_y, cell_size;
				string tmp;

				// get the dimensions, origin
				ss >> tmp >> cols >> tmp >> rows >>
					tmp >> ll_x >> tmp >> ll_y >>
					tmp >> cell_size;


				// create the elevation object
				ElevationData *elev_data = new ElevationData(rows, cols);
				elev_data->setxll(ll_x);
				elev_data->setyll(ll_y);
				elev_data->setCellSize(cell_size);

				// load the elevation data
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < cols; j++) {
						ss >> elev_val;
						elev_data->setVal(i, j, elev_val);
					}
				}
				return elev_data;
			}

	}; // class DataSource
} // namespace bridges
#endif
