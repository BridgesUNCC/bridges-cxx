#ifndef GRAPH_ADJ_LIST
#define GRAPH_ADJ_LIST

#include <stdexcept> //out of range
#include <sstream> //stringstream

#include "SLelement.h" //DataStructure, string, unordered_map, iostream, using std

namespace bridges{
/**
 * @brief This class provides methods to represent adjacency list based graphs
 *
 * The class is simply a wrapper around the C++ STL unordered_map class and thus 
 * derives all its operations from it.
 *
 * Generic Parameters:
 *      K that is used as an index,
 *      E the application data type
 *
 * @author Kalpathi Subramanian
 * @date 6/29/15
 */
template<typename K, typename E>
class GraphAdjList : public DataStructure {
	public:
        /** 
		 * @brief This helper class is used by GraphAdjList to keep track of edge 
		 * information 
		 */
        class Edge {
            private:
										// The weight of this edge 
                unsigned int weight = 1;
										// The destination vertex of this edge */
                K vertex = K();
										// The application specific data of this edge */
                string edge_data;

			public:

				/**
				 * Constructs an edge with the given destination vertex, weight, 
				 *	and edge data.
				 * If an argument is not given its default is used. Default Weight: 1
				 *
				 * @param wt The edge weight
				 * @param v The terminating vertex
				 * @param data The edge data
				 */
                Edge(const K& v,const int& wt=1,const string& data=string()) : 
								weight(wt), vertex(v), edge_data(data) 
				{	
				}

				/** 
				 * Set edge weight to "wt" @param wt The edge weight 
				 */
                void setWeight(const unsigned int& wt) {
					weight = wt;
				}

                /** 
				 * @return The edge weight 
				 */
				int getWeight() const {
					return weight;
				}

				/** 
				 *	Sets terminating vetex to "dest" 
				 *	@param dest The terminating vertex 
				 **/
				void setVertex(const K& dest){
					vertex = dest;
				}

				/** 
				 *	@return The terminating vertex 
				 */
				K getVertex() const {
					return vertex;
				}

				/** 
				 * 	Sets edge data to "data" 
				 *	@param data Application data 
				 */
				void setEdgeData(const string& data){
					edge_data = data;
				}
				
				/** @return The edge data */
				string getEdgeData() const {
					return edge_data;
				}
		}; //end of Edge class

	private:

		/** 
		 *	Indexed map of this this graph's verticies 
		 */
		unordered_map<K, Element<E>> vertices; // useful to maintain their properties

		/** 
		 * Map of edge lists for this graph's 
		 */
		unordered_map<K, SLelement<Edge>*> adj_list; // holds the adjacency list of edges;

	public:
													// Destructor */
		virtual ~GraphAdjList() override {
			for(auto& p : adj_list){  //frees edges
				if (p.second){
					p.second->cleanup();
				}
			}
		}
        /** 
		 *	@return The string representation of this data structure type 
		 */
		virtual const string getDStype() const {
			return "graphl";
		}
        /**
		 * Adds a vertex of key "k" and value "e" to the graph, and initializes its 
		 * adjacency list.
		 * If this key already exists its value and all source associated edges with 
		 * be overwriten.
		 * If value "e" is not provided the default will be used.
		 *
		 * @param k The vertex key
		 * @param e The vertex data
		 */
		void addVertex(const K& k,const E& e= E()) {
		    stringstream conv; conv << k;
			vertices[k] = Element<E>(e, conv.str());
			if(adj_list[k]){
				adj_list.at(k)->cleanup(); 
				adj_list.at(k)=nullptr;
			}
		}
		/**
		 * Sets the edge from "src" to "dest", weight to "wt" and data to "data".
		 * This will overwrite the existing edge weight.
		 * If data is not provided the default will be used;
		 *
		 * @param src The key of the source Vertex
		 * @param dest The key of the destination Vertex
		 * @param wt The weight of the edge
		 * @param data The edge data
		 * @throw out_of_range If "src" or "dest" is non-existenet within this graph
		 * @throw bad_alloc If allocation of a graph adjacency list item failed
		 */
		void addEdge(const K& src,const K& dest,const unsigned int& wt,
									const string& data = string()) {
			try {
				vertices.at(src);
				vertices.at(dest);
			    if(wt==0){
					vertices.at(src).links.erase(&(vertices.at(dest)));} //remove link data
			    SLelement<Edge>* sle = adj_list.at(src);
			    while(sle)
                {
                    Edge ed = sle->getValue();
                    if(ed.getVertex() == dest)//edge already exists
                    {
                        ed.setWeight(wt); //change edge weight
                        ed.setEdgeData(data); //change edge data
                        sle->setValue(ed); //change slelement data
                        return;
                    }
                    sle = sle->getNext();
                }
								//edge doesn't already exist
								//creates default link data if none already present
				vertices.at(src).links[&(vertices.at(dest))];
                stringstream conv; conv << dest;
								// create edge
			    adj_list.at(src) = new SLelement<Edge>(adj_list.at(src),
									Edge(dest,wt,data),conv.str());
			}
			catch(const out_of_range& oor){cerr<<"Cannot addEdge between non-existent verticies"<<endl;throw;}
		}

		/** 
		 *	@return The index map of this graph's verticies 
		 */
        const unordered_map<K, Element<E>>& getVertices() const {
			return vertices;
		}

		/** 
		 *	@return The adjacency lists 
		 */
        const unordered_map<K, SLelement<Edge>*>& getAdjacencyList() const {
				return adj_list;
		}

		/**
		 * Returns adjacency list of key "k"
		 *
		 * @param k The key of the source vertex
		 * @throw out_of_range If key is non-existent within this graph
		 * @return The adjacency list of key "k"
		 */
		const SLelement<Edge>* getAdjacencyList(const K& k) const {
			try{
				return adj_list.at(k);
			}
			catch(const out_of_range& oor){
				cerr<<"Cannot getAdjacencyList() of a non-existent vertex!"<<endl; throw;
			}
		}
    private:
		/**
		 * Gets the JSON representation of this Graph's nodes and links
		 *
		 * @param arr_size The size of the array determined by this
		 * @return A pair holding the nodes and links JSON strings respectively
		 */
		virtual const pair<string,string> getDataStructureRepresentation(const 
							unsigned int& arr_size) const override {

			unordered_set<const Element<E>*> nodes;
            for(unsigned int i=0;i<arr_size;i++) {
										// each pair<K,Element> in vertices
                for(const auto& key_ele : this[i].vertices) { 
                    nodes.emplace(&(key_ele.second));
                }
            }
			return Element<E>::generateJSON(nodes); // generate the JSON
		}

}; //end of GraphAdjList class

}//end of bridges namespace
#endif

