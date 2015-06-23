#ifndef EDGE_H

#define EDGE_H

#include <string>

using namespace std;
/**
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
class Edge {

	private:
		int weight;
		string vertex; // refers to a terminating vertex

	public:
		/**
		 * Construct an edge with no terminating Element - used only for graphs
		 */
		Edge() {
			weight = 0;
			vertex = "";
		}
	
		/**
		 * 	Construct an edge with thickness equal to "wt" and no 
		 *	terminating Element, used only for graphs.
		 * 	@param wt  integer representing edge weight, 
		 **/
		Edge(int wt) : Edge() {
			weight = wt;
		}
	
		/**
		 * 	Construct an edge, given edge weight and terminating vertex
		 * @param wt integer representing the edge weight(application dependent)
		 * @param v  terminating vertex id
		 **/
		Edge(int wt, string v) {
			weight = wt;
			vertex = v;
		}
	
		/**
		 * Set edge weight to "wt"
		 * 
		 * @param wt  integer representing the edge weight
		 **/
		void setWeight(int wt) {
			weight = wt;
		}
	
		/**
		 * Get edge weight
		 * 
		 * @return the thickness of the arrow in the Bridges Visualization
		 **/
		int getWeight() {
			return weight;
		}
	
		/**
		 * Set terminating Element of the edge
		 * 
		 * @param v the string identifier of the terminating Element
		 **/
		void setVertex(string v) {
			vertex = v;
		}
	
		/**
		 * Get identifer of the terminating Element of edge
		 * 
		 * @return the string identifier of the terminating vertex
		 */
		string getVertex() {
			return vertex;
		}
	
		/**
		 * Set edge to thickness of "wt" and terminating Elememt of "v".
		 * 
		 * @param wt integer representing the edge weight 
		 * @param v the string identifier of the terminating Element
		 */
		void setEdge(int wt, string v) {
			weight = wt;
			vertex = v;
		}
	
		/**
		 * Returns this edge
		 */
		Edge *getEdge() {
			return this;
		}
		
//		public int compareTo(Edge e1){
//			return ((Integer)this.getWeight()).compareTo((Integer)this.getWeight());
//		}
};

#endif
