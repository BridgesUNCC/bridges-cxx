#ifndef GRAPH_LIST_H

#define GRAPH_LIST_H

#include <string>
#include <new>
#include <unordered_map>

using namespace std;

#include "SLelement.h"
#include "Edge.h"

/**
 *	This class is a helper class for representing adjacency lists in graph
 *	based data structures.
 *
 *  The adjacency list based graph data structure in BRIDGES is represented 
 *  as an unordered map, as follows:
 *
 *    unordered_map<string, GraphList>
 *
 *   The string index permits a variety of datasets to be represented as
 *   graphs, for instance, Twitter or Facebook data, where user names(strings) 
 *	 are the vertices and linked to other users, represented by edges. The 
 *   GraphList facilitates a singly linked list(using SLelements). Methods
 *	 to created edges are provided. Edges are inserted into the front of the
 *   the list and are not in any particular order. 
 * 
 *
 *	<E> generic parameter, relating to the application specific data object
 *
 **/

template<typename E> class GraphList{
					// vertex of the graph
	private:
		SLelement<E> *src_vertex;
						// corresponding adjacency list
		SLelement<Edge> *adj_list;

//		GraphList<E>(const GraphList<E>&) {} // protect copy constructor
//		GraphList<E>& operator=(const GraphList<E>&) {} // protect assignment
	
	public:
		/**
	 	*  Constructor
		*  creates a GraphList object
		**/
		GraphList<E> (){
			src_vertex = NULL;
			adj_list = NULL;
		}
	
		/**
		 *	return the source vertex
		 *
		 * @return  the source vertex  for this adjacency list
		 **/
		SLelement<E> *getSourceVertex() {
			return src_vertex;
		}
	
		/**
		 *	 set the source vertex
		 *
		 *   @param v  incoming vertex
		 */
		void  setSourceVertex(SLelement<E> *v) {
			src_vertex = v;
		}
	
		/**
		 *	@return  the adjacency list 
		 **/
		SLelement<Edge> *getAdjacencyList() {
			return adj_list;
		}
	
		/**
		*	set the source vertex
		*   @param list  incoming adjacency list
		*/
		
		void  setAdjacencyList(SLelement<Edge> *list) {
			adj_list = list;
		}
	
		/**
		*	add an edge to the adjacency list
		*   @param e incoming new edge 
		*/
	
		void  addEdge(Edge e) {
									// insert at front
			try {
				adj_list = new SLelement<Edge> (e, adj_list);
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (in GraphList::addEdge()) caught: " 
						<< ba.what() << endl;
			}
		}
	
		/**
		 *	 add an edge to the adjacency list
		 *
		 *   @param vertex  : terminating vertex
		 *   @param weight  : edge weight 
		 */
		void addEdge (string vertex, int weight) {
			try {
				adj_list = new SLelement<Edge> (new Edge(weight, vertex), 
							adj_list);
			}
			catch (std::bad_alloc& ba) {
				cerr << "bad_alloc (in GraphList:addEdge()) caught: " 
                        << ba.what() << endl;
			}
		}
};

#endif
