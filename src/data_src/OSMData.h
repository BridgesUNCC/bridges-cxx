#ifndef OSM_DATA

#define OSM_DATA

#include "OSMVertex.h"
#include "OSMEdge.h"

namespace bridges {
	/**
	 * @brief  Class that hold Open Street Map vertices
	 *
	 * Class that holds Open Street Map data, from https://openstreetmap.org
	 *
	 * Kalpathi Subramanian, 2/16/19
	 *
	 */

	class OSMData {
		private:
			string name = "";
										// data range
			double latitude_range[2] = {0.0, 0.0}, 
					longitude_range[2] = {0.0, 0.0};
										// vertices 
			vector<OSMVertex> vertices;
										// edges
			vector<OSMEdge> edges;

		public:

			OSMData() {
			}

			/**
			 *   get the name of the dataset
			 *
			 *   @return  name (string)
			 *
			 */
			string getName() const {
				return name;
			}
			/**
			 *   get the name of the dataset
			 *
			 *   @param  name (string)
			 *
			 */
			void setName(string n) {
				name = n;
			}

			/**
			 *   get the range of the dataset 
			 *
			 *   @param  lat_range 
			 *   @param  longit_range 
			 *	 @return none
			 */
			void getLatLongRange (double *lat_range, double *longit_range) {
				lat_range[0] = latitude_range[0];
				lat_range[1] = latitude_range[1];
				longit_range[0] = longitude_range[0];
				longit_range[1] = longitude_range[1];
			}
			/**
			 *   set the range of the dataset 
			 *
			 *   @param  lat_range 
			 *   @param  longit_range 
			 *	 @return none
			 *
			 */
			void setLatLongRange (double *lat_range, double *longit_range) {
				latitude_range[0] = lat_range[0];
				latitude_range[1] = lat_range[1];
				longitude_range[0] = longit_range[0];
				longitude_range[1] = longit_range[1];
			}
			/**
			 *   get vertices
			 *
			 *   @return  vertices (std::vector) 
			 *
			 */
			void getVertices () {
				return vertices;
			}
			/**
			 *   set vertices
			 *
			 *   @param  vertices (std::vector) 
			 *
			 */
			void setVertices (vector<OSMVertex> verts) {
				vertices = verts;
			}
			/**
			 *   get edges
			 *
			 *   @return  edges (std::vector) 
			 *
			 */
			void getEdges () {
				return edges;
			}
			/**
			 *   set edges
			 *
			 *   @param  edges (std::vector) 
			 *
			 */
			void setEdges (vector<OSMVertex> e) {
				edges = e;
			}
	}

} // end namespace bridges

#endif
