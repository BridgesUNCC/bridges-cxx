
#include <string>

using namespace std;
/**
 * @brief This helper class is used by the graph 
 *  classes - GraphAdjList , GraphAdjMatrix -  to keep track of edge 
 *  information 

 * This class is used to assign a visual connection between two Elements in the
 * Bridges Visualization. 
 * <p>
 * Bridges will represent these as arrows between two
 * Elements. The starting Element of the arrow will be referred to as the source
 * Element and the ending Element of the arrow will be referred to as the
 * terminating Element.
 * 
 * @author krs
 *
 * @param <E>
 */

#ifndef EDGE_H

#define EDGE_H

namespace bridges{

template <typename K> 
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
						weight(wt), vertex(v), edge_data(data) {	
		}

		/** 
		 * 	Set edge weight to "wt" 
		 *
		 *	@param wt The edge weight 
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
		 *
		 *	@param dest The terminating vertex 
		 */
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
				
		/** 
		 *	@return The edge data 
		 */
		string getEdgeData() const {
			return edge_data;
		}
	}; //end of Edge class

} // end of bridges namespace
#endif