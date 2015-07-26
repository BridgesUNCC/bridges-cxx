


#ifndef GRAPH_ADJ_MATRIX_H

#define GRAPH_ADJ_MATRIX_H

#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

namespace bridges{

/**
 *
 * @brief This class provides methods to represent adjacency list based
 *		graphs

 * The GraphAdjMatrix class can be used to represent adjacency matrix based 
 * graphs in BRIDGES, with Key representing a data specific generic parameter.
 * The class is simply a wrapper  around the C++ STL  unordered_map class
 * and, thus, derives all its operations from it.  Given the use  of
 * operator overloading, the adjacency matrix implementation is almost 
 * identical to a normal array representation, except that any ordered type
 * can be used to index into the matrix.
 * <p>
 * BRIDGES provides methods to visualize the graph  and its contents. 
 *
 * @param Key is any orderable type, used as index into the adjacency matrix
 * @param  E  used to represent application specific data and is any legal
 *			 C++ type
 *
 *  @author Kalpathi Subramanian (C++ port)
 *
 *  @date 6/29/15
 *
 */
template <typename Key, typename E> class GraphAdjMatrix {
	private:
						// keep track of the graph nodes; useful
						// to maintain their properties
						// holds the adjacency matrix of edges
		unordered_map<Key, Element<E> > *vertices;

						// adjacency matrix
		unordered_map <Key, unordered_map<Key, double> > *matrix;

	public:

		/// Constructor

		GraphAdjMatrix() {		// clear the maps
			vertices = new unordered_map<Key, Element<E> >;
			matrix = new unordered_map <Key, unordered_map<Key, double> >;
			vertices->clear();
			matrix->clear();
		}

		/// 
		/// Adds a new vertex to the graph, setts the edge to itself to be
		//  of weght 0. User is responsible for checking if the vertex already
		/// exists. This method will replace the value for this key
		/// 
		/// @param Key - vertex key value 
		/// @return none
		/// 

		void addVertex(Key k, E e) {
					// note: it is the user's responsibility to  check
					// for duplicate edges (will be overwritten, otherwise)
			stringstream ss;
			ss << k;
			(*vertices)[k] = Element<E>(ss.str(), e);
					// initialize this row of items
			for (auto& key : *vertices) {
				(*matrix)[k][key.first] = (*matrix)[key.first][k] = 0.;
			}
		}

		/// 
		/// Adds a new edge to the graph, user is responsible for checking 
		/// if the edge already exists. This method will replace the value 
		/// for this key, otherwise
		/// 
		/// @param src - source vertex of edge
		/// @param dest - destination  vertex of edge
		/// @return none
		/// 
		void addEdge(Key src, Key dest, int weight) {
					// note: it is the user's responsibility to  check
					// if the edge already exists
			(*matrix)[src][dest] = weight; 
		}

		/** 
		 * This method returns the adjacency matrix
		 *
		 * @return matrix - the graph's adjacency matrix representation
		 *
		 **/
		unordered_map <Key, unordered_map<Key, double> > *getMatrix() {
			return matrix;
		}

		/** 
		 * This method returns the graph nodes
		 *
		 * @return -- vertices held in an unordered  map
		 *
		 **/
		unordered_map <Key, Element<E> > *getVertices() {
			return vertices;
		}
};


}
#endif

