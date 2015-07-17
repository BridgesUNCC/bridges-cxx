

#ifndef GRAPH_ADJ_LIST

#define GRAPH_ADJ_LIST

#include <unordered_map>
#include <sstream>

using namespace std;

#include "SLelement.h"
#include "Edge.h"

///
/// The GraphAdjList class can be used to represent adjacency list based 
/// graphs in BRIDGEs, with E represnting a data specific generic parameter.
///	The class is simply a wrapper  around the C++ STL  unordered_map class
///	and, thus, derives all its operations from it.
///	BRIDGES provides methods to visualize the graph  and its contents. 
///	
///	Author: Kalpathi Subramanian, 6/29/15
///	
///	@param Element<E>
///	

namespace bridges {

template<typename Key, typename E> class GraphAdjList{
	private: 

						// keep track of the graph nodes; useful
						// to maintain their properties
        unordered_map<Key, Element<E> > *vertices;

						// holds the adjacency list of edges
		unordered_map<Key, SLelement<Edge<Key> >* > *adj_list;

	public:
		/// 
		/// Constructor 
		/// 
		GraphAdjList() {
			vertices = new unordered_map<Key, Element<E> >;
			adj_list = new unordered_map<Key, SLelement<Edge<Key> >* >;
			vertices->clear();
			adj_list->clear();
		}	
		~GraphAdjList(){
			delete vertices;
			delete adj_list;
		}

		/// 
		/// Adds a new vertex to the graph, initializes the  adjacency
		/// list; user is responsible for checking if the vertex already
		/// exists. This method will replace the value for this key
		/// 
		/// @param Key - vertex key value 
		/// @return none
		/// 

		void addVertex(Key k, E e) {
					// note: it is the user's responsibility to  check
					// for duplicate vertices
			stringstream ss; ss << k;
			(*vertices)[k] = Element<E>(ss.str(), e);
			(*adj_list)[k] = NULL;
		}

		/// 
		/// Adds a new edge to the graph, initializes the  adjacency
		/// list; user is responsible for checking if the vertex already
		/// exists. This method will replace the value for this key
		/// 
		/// @param src - source vertex of edge
		/// @param dest - destination  vertex of edge
		/// @return none
		/// 
		void addEdge(Key src, Key dest, int weight) {
					// note: it is the user's responsibility to  check
					// if the edge already exists
			stringstream ss; ss << dest;
			(*adj_list)[src] = 
				new SLelement<Edge<Key> > (Edge<Key>(weight, ss.str()), (*adj_list)[src]); 
		}
		/// 
		/// This method returns the graph nodes
		/// 
		///@return -- vertices held in an unordered  map
		///
		///
        unordered_map <Key, Element<E> > *getVertices() {
            return vertices;
        }

		/// 
		/// Gets the adjacency list (of type SLelement<Edge> *)
		/// 
		///
		/// @return - the graph's adjacency lists 
		///
		unordered_map<Key, SLelement<Edge<Key> >* > *getAdjacencyList() {
			return adj_list; 
		}
		/// 
		/// Gets the adjacency list (of type SLelement<Edge> * of a vertex)
		/// 
		/// @param - vertex key
		///
		/// @return - the graph's adjacency list  corresponding to this vertex
		///
		SLelement<Edge<Key> >*  getAdjacencyList(Key vertex) {
			return (*adj_list)[vertex]; 
		}
};


}
#endif

