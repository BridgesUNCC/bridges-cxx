/**
 *
 * The GraphAdjMatrix class can be used to represent adjacency matrix based 
 * graphs in BRIDGES, with T representing a data specific generic parameter.
 * The class is simply a wrapper  around the C++ STL  unordered_map class
 * and, thus, derives all its operations from it.
 * BRIDGES provides methods to visualize the graph  and its contents. 
 *
 * Author: Kalpathi Subramanian, 7/1/15
 *
 * @param Element<E>
 *
 */



#ifndef GRAPH_ADJ_MATRIX_H

#define GRAPH_ADJ_MATRIX_H

#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

namespace bridges{
//template <typename Key> using GraphAdjMatrix = unordered_map <Key, 
//					unordered_map<T, double> >;

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
			matrix[k][k] = 0.;
			stringstream ss;
			ss << k;
			vertices[k] = Element<E>(ss.str(), e);
			for (auto& key : vertices) {
				matrix[k][key.first] = matrix[key.first][k] = 0.;
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
			matrix[src][dest] = weight; 
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

