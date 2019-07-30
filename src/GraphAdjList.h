#ifndef GRAPH_ADJ_LIST
#define GRAPH_ADJ_LIST

#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <JSONutil.h>

using namespace std;

#include "SLelement.h"
#include "Edge.h"

namespace bridges {
	namespace datastructure {
		/** @brief This class provides methods to represent adjacency list
		 *	based graphs.
		 *
		 *  The class is simply a wrapper around the C++ STL unordered_map
		 *	class and thus derives all its operations from it.
		 *
		 *  @param K: used as an index to retrieve vertices,
		 *  @param E1: data type used to store vertex specific information,
		 *  @param E2: data type used to store edge specific information
		 *
		 * @author Kalpathi Subramanian
		 * @date Last modified 4/22/18, 7/12/19
		 *
		 * There is a tutorial about Graph Adjacency List  :
		 * http://bridgesuncc.github.io/tutorials/Graph_AL.html
		 *
		 */
		template<typename K, typename E1 = K, typename E2 = E1>
		class GraphAdjList : public DataStructure {
			private:
				// list of graph vertices
				// maintained as a map to accommodate strings
				unordered_map<K, Element<E1>* > vertices;
				// adjacency lists
				unordered_map<K, SLelement<Edge<K, E2> >*> adj_list;

				// large graph related
				static const int LargeGraphVertSize = 2000;

				bool forceLargeViz = false;
				bool forceSmallViz = false;

				const string getCSSRepresentation(const Color& col) const {
					using bridges::JSONUtil::JSONencode;
					if (col.isTransparent()) {
						//leaves off other channels if transparent
						return "[0, 0, 0, 0.0]";
					}

					const string strCSS =
						JSONencode(col.getRed()) + "," +
						JSONencode(col.getGreen()) + "," +
						JSONencode(col.getBlue()) + "," +
						JSONencode(col.getAlpha() / 255.0, 3);
					//				JSONencode( ((float) (col.getAlpha()) / 255.0f));

					return OPEN_BOX + strCSS + CLOSE_BOX;
				}

				GraphAdjList(const GraphAdjList& gr) = delete; //would not be correct
				const GraphAdjList& operator= (const GraphAdjList& gr) = delete; //would not be correct
			public:

				GraphAdjList() = default;
				GraphAdjList(GraphAdjList&& gr) = default;

				virtual ~GraphAdjList() override {
					for (auto& v : vertices) {
						if (adj_list[v.first]) {
							// discard the edges in the adj. list
							SLelement<Edge<K, E2>> *tmp;
							for (SLelement<Edge<K, E2>> *sle =
									adj_list[v.first]; sle != nullptr; ) {
								tmp = sle;
								sle = sle->getNext();
								delete tmp;
							}
							delete vertices[v.first]; // free the element at v
							adj_list[v.first] = nullptr;
						}
					}
				}
				/**
				 *	@return The string representation of this data structure type
				 */
				virtual const string getDStype() const override {
					if (forceLargeViz || (!forceSmallViz &&
							vertices.size() > LargeGraphVertSize &&
							areAllVerticesLocated())) {
						return "largegraph";
					}
					return "GraphAdjacencyList";
				}

				/**
				 * 	Adds a vertex of key "k" and value "e" to the graph,
				 *	and initializes its adjacency list; If this key already
				 *	exists  then this will not create a new vertex.
				 *
				 *
				 * @param k The vertex key
				 * @param e The vertex data
				 *
				 */
				void addVertex(const K& k, const E1& e = E1()) {
					stringstream conv;
					conv << k;
					if (vertices.find(k) == vertices.end()) {
						// vertex does not exist, create one
						vertices[k] = new Element<E1>(e, conv.str());
						adj_list[k] = nullptr;
					}
				}
				/**
				 * 	@brief add an edge with data.
				 *
				 *      Note that this function adds the edge regardless of
				 *	the contents of the adjacency list; its the user's responsibility
				 *	to ensure there are no duplicates and ensure consistency.
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 * @param data The edge data
				 * @throw out_of_range If "src" or "dest" is non-existent within
				 *	this graph
				 * @throw bad_alloc If allocation of a graph adjacency list item failed
				 */
				void addEdge(const K& src, const K& dest, const E2& data = E2()) {
					try {
						vertices.at(src);
						vertices.at(dest);
						// links structure is redundant and needs
						// to be removed in future implementations!
						vertices[src]->links[vertices.at(dest)]; //In C++ this creates the linkvisualizer

						stringstream conv;
						conv << dest;
						// add the edge
						adj_list.at(src) =
							new SLelement<Edge<K, E2> > (adj_list.at(src),
							Edge<K, E2> (src, dest, &(vertices[src]->links[vertices.at(dest)]), data), conv.str());

					}
					catch ( const out_of_range& ) {
						cerr << "addEdge(): Nonexistent vertex?" << endl <<
							"Create vertices first prior to adding edges that use that vertex" << endl
							<<  "Cannot add edge between non-existent verticies"
							<< endl;
						throw;
					}
				}
				/**
				 * 	Gets vertex data for a graph vertex
				 *
				 * @param src The key of the source vertex
				 *
				 * @return E1  vertex specific data
				 */
				const E1&  getVertexData (const K& src)& {
					try {
						Element<E1> *el = vertices.at(src);
						return  (vertices.at(src))->getValue();
					}
					catch ( const out_of_range& ) {
						cerr << "getVertexData(): vertex not found" << endl;
						throw;
					}
					// should never reach here
					throw "getVertexData(): vertex not found";
				}
				/**
				 * 	Loads vertex specific information for a graph vertex
				 *
				 * @param vertID The key of Vertex
				 * @param data data to set
				 *
				 */
				void setVertexData (const K& vertID, E1 const & data) {
					try {
						Element<E1> *el = vertices.at(vertID);
						el->setValue (data);
					}
					catch ( const out_of_range& ) {
						cerr << "setVertexData(): Nonexistent vertex" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
				}
				/**
				 * 	Gets edge data for the edge from "src" to "dest"
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 *
				 * @return   edge specific data
				 */
				E2&  getEdgeData (const K& src, const K& dest) {
					try {
						vertices.at(src);
						vertices.at(dest);
						SLelement<Edge<K, E2> > *sle = adj_list.at(src);
						while (sle) {
							Edge<K, E2> ed = sle->getValue();
							if (ed.getVertex() == dest) { //edge exists
								return ed.getEdgeData();
							}
							sle = sle->getNext();
						}
						throw "Edge not found!";
					}
					catch ( const out_of_range& ) {
						cerr << "getEdgeData(): Edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
					// should never reach here
					throw "getEdgeData(): Edge not found";
				}
				/**
				 * 	Gets edge data for the edge from "src" to "dest" - const version
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 *
				 * @return edge specific data
				 */
				E2 const&  getEdgeData (const K& src, const K& dest) const {
					try {
						vertices.at(src);
						vertices.at(dest);
						SLelement<Edge<K, E2> > *sle = adj_list.at(src);
						while (sle) {
							Edge<K, E2> ed = sle->getValue();
							if (ed.getVertex() == dest) { //edge exists
								return ed.getEdgeData();
							}
							sle = sle->getNext();
						}
						throw "Edge not found!";
					}
					catch ( const out_of_range& ) {
						cerr << "getEdgeData(): Edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
					// should never reach here
					throw "getEdgeData(): Edge not found";
				}


				/**
				 * 	Loads edge specific information for the edge from "src" to
				 *   "dest"
				 *
				 * @param src The key of the source Vertex
				 * @param dest The key of the destination Vertex
				 * @param data  edge data
				 *
				 */
				void setEdgeData (const K& src, const K& dest, E2& data) {
					try {
						vertices.at(src);
						vertices.at(dest);
						SLelement<Edge<K, E2> > *sle = adj_list.at(src);
						while (sle) {
							Edge<K, E2> ed = sle->getValue();
							if (ed.getVertex() == dest) { //edge exists
								ed.setEdgeData(data); //change edge data
								sle->setValue(ed); //change slelement data
								return;
							}
							sle = sle->getNext();
						}
						throw "getEdgeData(): Edge not found!";
					}
					catch ( const out_of_range& ) {
						cerr << "setEdgeData(): Nonexistent vertices or " <<
							" edge not found" << endl;
						throw;
					}
					catch (const char* msg) {
						cerr << msg << endl;
					}
					// will never reach here, but avoids compiler warnings
					throw "getEdgeData(): Edge not found";
				}
				/**
				 *  Return the graph nodes
				 *
				 *	@return The vertex list of this graph
				 */
				unordered_map<K, Element<E1>*>* getVertices() {
					return &vertices;
				}

				/**
				 *  Return the graph nodes - const version
				 *
				 *	@return The vertex list of this graph
				 */
				const unordered_map<K, Element<E1>*>* getVertices() const {
					return &vertices;
				}
				/**
				 *  Return the vertex corresponding to a key
				 *	@return the requested vertex of this graph or nullptr if not found
				 */
				const Element<E1>* getVertex(const K& key) const {
					try {
						return vertices.at(key);
					}
					catch (const std::out_of_range& oor) {
						/* std::cerr << "Out of Range error: " << oor.what() */
						/* 	<< "returning null pointer\n"; */
						return nullptr;
					}
				}


				/**
				 *  Return the requested vertex corresponding to a key - non-const version
				 *	@return the requested vertex of this graph or nullptr if not found
				 *
				 */
				Element<E1>* getVertex(const K& key) {
					try {
						return vertices.at(key);
					}
					catch (const std::out_of_range& oor) {
						/* std::cerr << "Out of Range error: " << oor.what() */
						/* 	<< "returning null pointer\n"; */
						return nullptr;
					}
				}


				/**
				 *  Return the adjacency list
				 *	@return The adjacency list  of the graph
				 */
				const unordered_map<K, SLelement<Edge<K, E2> >*>&
				getAdjacencyList() const {
					return adj_list;
				}

				/**
				 * Returns adjacency list of a vertex with name k
				 *
				 * @param k The key of the source vertex
				 * @throw out_of_range If key is non-existent within this graph
				 *
				 * @return The adjacency list of key "k"
				 */
				SLelement<Edge<K, E2> >* getAdjacencyList(const K& k) {
					try {
						return adj_list.at(k);
					}
					catch (const out_of_range& ) {
						cerr <<  "Cannot getAdjacencyList() of a non-existent vertex!"
							<< endl;
						throw;
					}
				}

				/**
				 * Returns adjacency list of a vertex with name k - const version
				 *
				 * @param k The key of the source vertex
				 * @throw out_of_range If key is non-existent within this graph
				 *
				 * @return The adjacency list of key "k"
				 */
				const SLelement<Edge<K, E2> >* getAdjacencyList(const K& k) const {
					try {
						return adj_list.at(k);
					}
					catch (const out_of_range& ) {
						cerr <<  "Cannot getAdjacencyList() of a non-existent vertex!"
							<< endl;
						throw;
					}
				}


				/**
				 *  Returns the  visualizer corresponding to  a graph vertex;
				 *	convenient method to set attributes of the graph vertex
				 *
				 *  @param k The key of the graph vertex
				 *
				 *  @return the visualizer that controls the attributes  of this node
				 */
				ElementVisualizer *getVisualizer (const K& k) {
					try {
						Element<E1> *el = vertices.at(k);

						return el->getVisualizer();
					}
					catch (const out_of_range& ) {
						cerr <<  "Graph vertex " << k << " not found in graph!" << endl;
						throw;
					}
				}
				/**
				 *  Returns the link visualizer corresponding to two graph
				 *	nodes with an existing link; error returned if no link exists.
				 *
				 *  @param k1 The key of the link source vertex
				 *  @param k2 The key of the link destination  vertex
				 *
				 * @return the visualizer that controls the attributes  of this link
				 */
				LinkVisualizer *getLinkVisualizer (const K& k1, const K& k2) {
					try {
						Element<E1> *el1 = vertices.at(k1);
						Element<E1> *el2 = vertices.at(k2);

						return el1->getLinkVisualizer(el2);
					}
					catch (const out_of_range& ) {
						cerr <<  "Either source or destination node not found in graph!"
							<< endl;
						throw;
					}
				}
			private:
				/**
				 * Gets the JSON representation of this Graph's nodes and links
				 *
				 * @return A pair holding the nodes and links JSON strings respectively
				 */
				virtual const string getDataStructureRepresentation() const override {
					using bridges::JSONUtil::JSONencode;

					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs

					// check for large graph
					if (forceLargeViz ||
						(!forceSmallViz &&
							vertices.size() > LargeGraphVertSize &&
							areAllVerticesLocated())) {
						return getDataStructureRepresentationLargeGraph();
					}

					unordered_map<K, int> node_map;
					int i = 0;
					string nodes_JSON = "", links_JSON = "";

					for (const auto& v : vertices) {
						if (node_map.emplace(v.first, i).second) {
							i++;
							nodes_JSON += v.second->getElementRepresentation() + COMMA;
						}
					}

					//Remove trailing comma and nullptr entry

					if (nodes_JSON.size()) {
						nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
					}

					// iterate through the vertices and form the links JSON

					for (const auto& v : vertices) {
						// get adj. list
						Element<E1>* src_vert = vertices.at(v.first);
						// iterate through list and form links
						for (SLelement<Edge<K, E2>>* it = adj_list.at(v.first); it != nullptr;
							it = it->getNext()) {
							Element<E1>* dest_vert = vertices.at(it->getValue().to() );
							links_JSON +=  src_vert->getLinkRepresentation(
									*(src_vert->getLinkVisualizer(dest_vert)),
									JSONencode(node_map.at(v.first)),
									JSONencode(node_map.at(it->getValue().to())) ) + COMMA;
						}
					}

					//Remove trailing comma
					if (links_JSON.size()) {
						links_JSON = links_JSON.erase(links_JSON.size() - 1);
					}

					string graph_alist_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX + nodes_JSON + CLOSE_BOX + COMMA +
						QUOTE + "links" + QUOTE + COLON + OPEN_BOX +
						links_JSON + CLOSE_BOX +
						CLOSE_CURLY;


					return graph_alist_json;
				}
				/**
				 *
				 *  For large graphs, we will use a very lean representation,
				 *	just the nodes and links and
				 *  only the color property; currently this is for OSM data
				 *	only. Contain only location and
				 *	color attributes
				 *
				 */

				string getDataStructureRepresentationLargeGraph () const {

					using bridges::JSONUtil::JSONencode;
					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs

					unordered_map<K, int> node_map;
					int i = 0;
					string nodes_JSON = "";

					for (const auto& v : vertices) {
						if (node_map.emplace(v.first, i).second) {
							i++;
							const ElementVisualizer *elvis =
								vertices.at(v.first)->getVisualizer();
							string loc_str = "";
							if ( (elvis->getLocationX() != INFINITY) &&
								(elvis->getLocationY() != INFINITY) ) {
								loc_str =
									OPEN_BOX +
									JSONencode(elvis->getLocationX())  + COMMA +
									JSONencode(elvis->getLocationY()) +
									CLOSE_BOX + COMMA;
							}
							nodes_JSON +=  OPEN_BOX + loc_str +
								getCSSRepresentation(elvis->getColor()) +
								CLOSE_BOX + COMMA;
						}
					}

					//Remove trailing comma and nullptr entry

					if (nodes_JSON.size()) {
						nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
					}

					// next link information
					string links_JSON =  "";
					for (const auto& v : vertices) {
						// get adj. list
						Element<E1>* src_vert = vertices.at(v.first);
						// iterate through list and form links
						for (SLelement<Edge<K, E2>>* it = adj_list.at(v.first); it != nullptr;
							it = it->getNext()) {
							Element<E1>* dest_vert = vertices.at(it->getValue().to() );
							LinkVisualizer *lv = src_vert->getLinkVisualizer(dest_vert);
							string src = JSONencode(node_map.at(v.first));
							string dest = JSONencode(node_map.at(it->getValue().to()));
							links_JSON +=  OPEN_BOX +
								src  + COMMA +
								dest + COMMA +
								getCSSRepresentation(lv->getColor()) +
								CLOSE_BOX + COMMA;

						}
					}
					//Remove trailing comma
					if (links_JSON.size())
						links_JSON = links_JSON.erase(links_JSON.size() - 1);

					string graph_alist_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX + nodes_JSON + CLOSE_BOX + COMMA +
						QUOTE + "links" + QUOTE + COLON +
						OPEN_BOX + links_JSON + CLOSE_BOX +
						CLOSE_CURLY;

					return graph_alist_json;

				}
				/**
				 * @return true if all vertices have both an x and y location
				 */
				bool areAllVerticesLocated() const {
					for (const auto& v : vertices) {
						ElementVisualizer *elvis = v.second->getVisualizer();
						if (elvis->getLocationX() == INFINITY
							|| elvis->getLocationY() == INFINITY)
							return false;
					}
					return true;
				}


			public:

				void forceLargeVisualization(bool f) {
					if (f) {
						forceLargeViz = true;
						forceSmallViz = false;
					}
					else {
						forceLargeViz = false;
					}
				}

				void forceSmallVisualization(bool f) {
					if (f) {
						forceSmallViz = true;
						forceLargeViz = false;
					}
					else {
						forceSmallViz = false;
					}
				}

				///@brief This is a helper class to return sets of vertices ina  way that are iterable with range for loops. Students should not have to use this directly.
				class KeySet_helper {
						std::unordered_map<K, Element<E1>* > const & underlying_map;

					public:
						KeySet_helper (std::unordered_map<K, Element<E1>* > const  & um)
							: underlying_map(um)
						{}

						class const_iterator {
								typename std::unordered_map<K, Element<E1>* >::const_iterator it;
							public:
								const_iterator(typename std::unordered_map<K, Element<E1>* >::const_iterator i )
									: it(i)
								{}

								bool operator!=(const const_iterator& it) const {
									return this->it != it.it;
								}

								const K& operator*() const {
									return it->first;
								}

								const_iterator& operator++() {
									it ++;
									return *this;
								}
						};

						const_iterator begin() const {
							return const_iterator(underlying_map.begin());
						}

						const_iterator end() const {
							return const_iterator(underlying_map.end());
						}
				};

				///returns a set of all keys (read only) that conforms to STL list interface.
				///That means we can use range for
				KeySet_helper keySet() const {
					return KeySet_helper(this->vertices);
				}

				typename SLelement<Edge<K, E2>>::SLelement_listhelper outgoingEdgeSetOf(K const & k) {
					return typename SLelement<Edge<K, E2>>::SLelement_listhelper(getAdjacencyList(k));
				}

				typename SLelement<Edge<K, E2>>::SLelement_constlisthelper outgoingEdgeSetOf(K const & k) const {
					return typename SLelement<Edge<K, E2>>::SLelement_constlisthelper(getAdjacencyList(k));
				}


				///@brief This is a helper class to return sets of vertices in a way that are iterable with range for loops. Students should have to use this directly.
				class VertexElementSet_listhelper {
						typename std::unordered_map<K, Element<E1>* > & underlying_map;

					public:
						VertexElementSet_listhelper (std::unordered_map<K, Element<E1>* > & um)
							: underlying_map(um)
						{}

						///@brief This is a helper class to return sets of vertices in a way that are iterable with range for loops. Students should have to use this directly.
						class iterator {
								typename std::unordered_map<K, Element<E1>* >::iterator it;
							public:
								iterator(typename std::unordered_map<K, Element<E1>* >::iterator i )
									: it(i)
								{}

								bool operator!=(const iterator& it) const {
									return this->it != it.it;
								}

								Element<E1>*  operator*()  {
									return it->second;
								}

								iterator& operator++() {
									it ++;
									return *this;
								}
						};

						///@brief This is a helper class to return sets of vertices in a way that are iterable with range for loops. Students should have to use this directly.
						class const_iterator {
								typename std::unordered_map<K, Element<E1>* >::const_iterator it;
							public:
								const_iterator(typename std::unordered_map<K, Element<E1>* >::const_iterator i )
									: it(i)
								{}

								bool operator!=(const const_iterator& it) const {
									return this->it != it.it;
								}

								Element<E1> const*  operator*() const {
									return it->second;
								}

								const_iterator& operator++() {
									it ++;
									return *this;
								}
						};


						iterator begin() {
							return iterator(underlying_map.begin());
						}

						iterator end() {
							return iterator(underlying_map.end());
						}

						const_iterator begin() const {
							return const_iterator(underlying_map.begin());
						}

						const_iterator end() const {
							return const_iterator(underlying_map.end());
						}

				};

				///returns a set of vertices (Element<E>) that conforms to STL list interface. That means we can use range for
				VertexElementSet_listhelper vertexSet () {
					return VertexElementSet_listhelper(vertices);
				}


				///@brief This is a helper class to return sets of vertices ina  way that are iterable with range for loops. Students should not have to use this directly.
				class constVertexElementSet_listhelper {
						typename std::unordered_map<K, Element<E1>* > const & underlying_map;

					public:
						constVertexElementSet_listhelper (std::unordered_map<K, Element<E1>* > const& um)
							: underlying_map(um)
						{}

						///@brief This is a helper class to return sets of vertices ina  way that are iterable with range for loops. Students should not have to use this directly.
						class const_iterator {
								typename std::unordered_map<K, Element<E1>* >::const_iterator it;
							public:
								const_iterator(typename std::unordered_map<K, Element<E1>* >::const_iterator i )
									: it(i)
								{}

								bool operator!=(const const_iterator& it) const {
									return this->it != it.it;
								}

								Element<E1> const*  operator*() const {
									return it->second;
								}

								const_iterator& operator++() {
									it ++;
									return *this;
								}
						};

						const_iterator begin() const {
							return const_iterator(underlying_map.begin());
						}

						const_iterator end() const {
							return const_iterator(underlying_map.begin());
						}
				};
				///returns a set of vertices (Element<E>) that conforms to STL list interface. That means we can use range for
				constVertexElementSet_listhelper vertexSet () const {
					return constVertexElementSet_listhelper(vertices);
				}
		};

		//end of GraphAdjList class
	}
}//end of bridges namespace
#endif
