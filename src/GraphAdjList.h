

#ifndef GRAPH_ADJ_LIST

#define GRAPH_ADJ_LIST

#include <unordered_map>
#include <sstream>

using namespace std;

#include "SLelement.h"
#include "Edge.h"

namespace bridges {
/**

 * @brief This class provides methods to represent adjacency list based
 *  graphs

 * The GraphAdjList class can be used to represent adjacency list based 
 * graphs in BRIDGES.  
 * <p>
 *  In order to support any ordered type as index, this class is implemented
 *	as a wrapper  around the C++ STL  unordered_map class
 *	and, thus, derives all its operations from it. The Key parameter must
 *  an orderable type, while E represents any application data that is 
 *  maintained as part of the application.
 *  <p>
 *	BRIDGES provides methods to visualize the graph  and its contents. 
 *	
 *	
 *	Generic paramter Key used as index into the adjacency lists
 *  Generic parameter  E  used to represent application specific data
 *
 *	@author Kalpathi Subramanian, 6/29/15
 *  @date 6/29/15
 *	
 **/


template<typename Key, typename E> class GraphAdjList{
	private: 

						// keep track of the graph nodes; useful
						// to maintain their properties
        unordered_map<Key, Element<E> > *vertices;

						// holds the adjacency list of edges
		unordered_map<Key, SLelement<Edge<Key> >* > *adj_list;

	public:
		/** 
		 *  Constructors
		 */ 
		GraphAdjList() {
			vertices = new unordered_map<Key, Element<E> >;
			adj_list = new unordered_map<Key, SLelement<Edge<Key> >* >;
			vertices->clear();
			adj_list->clear();
		}	
		~GraphAdjList(){
								// need to free the edges (of type SLElement*)
			for (auto& v : *vertices) {
				for (SLelement<Edge<Key>>* sle = (*adj_list)[v.first]; 
											sle != NULL;) {
					SLelement<Edge<Key>>* next = sle->getNext();
					delete sle; sle = next;
				}
			}
			vertices->clear();
			adj_list->clear();
					 
			delete vertices;
			delete adj_list;
		}

		/** 
		 * Adds a new vertex to the graph, initializes the  adjacency
		 * list; user is responsible for checking if the vertex already
		 * exists. This method will replace the value for this key
		 * 
		 * @param k - vertex key value 
		 * 
		 */

		void addVertex(Key k, E e) {
					// note: it is the user's responsibility to  check
					// for duplicate vertices
			stringstream ss; ss << k;
			(*vertices)[k] = Element<E>(ss.str(), e);
			(*adj_list)[k] = NULL;
		}

		/** 
		 * Adds a new edge to the graph, initializes the  adjacency
		 * list; user is responsible for checking if the vertex already
		 * exists. This method will replace the value for this key
		 * 
		 * @param src - source vertex of edge
		 * @param dest - destination  vertex of edge
		 *
		 */ 
		void addEdge(Key src, Key dest, int weight) {
					// note: it is the user's responsibility to  check
					// if the edge already exists
			stringstream ss; ss << dest;
			(*adj_list)[src] = 
				new SLelement<Edge<Key> > (Edge<Key>(weight, ss.str()), 
											(*adj_list)[src]); 
		}
		/** 
		 * This method returns the graph nodes
		 * 
		 * @return vertices :  vertices held in an unordered  map
		 *
		 */
        unordered_map <Key, Element<E> > *getVertices() {
            return vertices;
        }

		/** 
		 * This method returns the graph node corresponding to the key k
		 * 
		 * @param  k : key
		 *
		 * @return : pointer to the graph node
		 *
		 */
		Element<E> *getVertex(Key k) {
			if (vertices->find(k) == vertices->end()) { // not found
				cerr << "Vertex " << k  << "not found!" << endl;
				return NULL;
			}
			return &((*vertices)[k]);
		}

		/** 
		 * Gets the adjacency list (of type SLelement<Edge> *)
		 * 
		 *
		 * @return - the graph's adjacency lists 
		 */
		unordered_map<Key, SLelement<Edge<Key> >* > *getAdjacencyList() {
			return adj_list; 
		}

		/** 
		 * Gets the adjacency list (of type SLelement<Edge> * of a vertex)
		 * 
		 * @param  vertex  the source vertex
		 *
		 * @return  the graph's adjacency list corresponding to this vertex
		 */
		SLelement<Edge<Key> >*  getAdjacencyList(Key vertex) {
			return (*adj_list)[vertex]; 
		}
};

}
#endif

