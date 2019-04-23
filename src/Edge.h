
#include <string>
using namespace std;

#include "LinkVisualizer.h"

#ifndef EDGE_H

#define EDGE_H

namespace bridges {

	/**
	 * @brief This helper class is used by the graph
	 *  classes - GraphAdjList , GraphAdjMatrix -  to keep track of edge
	 *  information
	 *
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


	template <typename K, typename E2 = K>
	class Edge {
		private:
			// The weight of this edge
			unsigned int weight = 1;

			// The source vertex of this edge */
			K fromv = K();

			// The destination vertex of this edge */
			K tov = K();

			// The application specific data of this edge */
			E2 edge_data = E2();

			// The link visualizer for this edge
		LinkVisualizer  *lvis;

		public:

			/**
			 * Constructs an edge with the given destination vertex, weight,
			 *	and edge data.
			 * If an argument is not given its default is used. Default Weight: 1
			 *
			 * @param wt edge weight
			 * @param from source  vertex
			 * @param to destination  vertex
			 * @param data edge data
			 */
	Edge(const K& v1, const K& v2, LinkVisualizer* lv, const E2& data = E2()) :
				fromv(v1), tov (v2), edge_data(data),lvis(lv) {

			}
			~Edge(){
				//lvis lifetime is managed by the graph itself
			}

			/**
			 *	@return The source vertex
			 */
			const K& from() const {
				return fromv;
			}


			/**
			 *	@return The terminating vertex
			 */
			const K& to() const {
				return tov;
			}

			/**
			 * 	Sets edge data to "data"
			 *	@param data Application data
			 */
			void setEdgeData(const E2& data) {
				edge_data = data;
			}

			/**
			 *	@return The edge data
			 */
			const E2& getEdgeData() const {
				return edge_data;
			}
			/**
			 *	@return The edge data
			 */
			E2& getEdgeData() {
				return edge_data;
			}
			/**
			 *  @return The label of the element
			 */
			string getLabel() const {
				return lvis->getLabel();
			}

			/**
			 * Sets label to "lab"
			 *
			 * @param lab The label of the element
			 */
			void setLabel(const string& lab) {
				lvis->setLabel(lab);
			}

			/**
			 * Set the thickness to "thick"
			 * Valid Range:[1,10] Default: 1
			 *
			 * @param thick The size in pixels of the link's line weight
			 * @throw string If invalid thickness
			 */
			void setThickness(const double& th) {
				lvis->setThickness(th);
			}
			/**
			 *	@return Size in pixels of the link's line thickness
			 */
			double getThickness() const {
				return lvis->getThickness();
			}

			/**
			 * Set the link weight to "wt"
			 * Valid Range: determined by application, can be negative
			 *
			 * @param wt The size in pixels of the link's line weight
			 * @throw string If invalid thickness
			 */
			void setWeight(const double& wt) {
				lvis->setWeight(wt);
			}

			/**
			 *	@return link weight
			 */
			double getWeight() const {
				return lvis->getWeight();
			}

			/**
			 * Set the color to "col", default black
			 *
			 * @param color The color of the element
			 */
			void setColor(const Color& col) {
				lvis->setColor(col);
			}
			/**
			 *	@return The color of the link
			 */
			Color getColor() const {
				return lvis->getColor();
			}
	}; //end of Edge class

} // end of bridges namespace
#endif
