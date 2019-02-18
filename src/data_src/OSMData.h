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
			double cartesian_range_x[2] = {0.0, 0.0},
					cartesian_range_y[2] = {0.0, 0.0};
										// vertices 
			vector<OSMVertex> vertices;
										// edges
			vector<OSMEdge> edges;

			double degreeToRadians(double deg) {
				return deg*M_PI/180.;
			}

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
			 *   get the Latitude and Longitude range of the dataset 
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
			 *   set the latitude and longitude range of the dataset 
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
			 *   set the range of the dataset 
			 *
			 *   @param  lat_min 
			 *   @param  long_min 
			 *   @param  lat_max,
			 *   @param  long_max,
			 *	 @return none
			 *
			 */
			void setLatLongRange (double lat_min, double lat_max, 
							double long_min, double long_max) {
				latitude_range[0] = lat_min;
				latitude_range[1] = lat_max;
				longitude_range[0] = long_min;
				longitude_range[1] = long_max;
			}
			/**
			 *   get the range of dataset in Cartesian coords
			 *
			 *   @param  xrange[2] 
			 *   @param  yrange[2] 
			 *	 @return none
			 */
			void getCartesianCoordsRange (double *xrange, double *yrange) {
				xrange[0] = cartesian_range_x[0];
				xrange[1] = cartesian_range_x[1];
				yrange[0] = cartesian_range_y[0];
				yrange[1] = cartesian_range_y[1];
			}
			/**
			 *   set the range of dataset in Cartesian coords
			 *
			 *   @param  xrange[2]
			 *   @param  yrange[2] 
			 *	 @return none
			 *
			 */
			void setCartesianCoordsRange (double *xrange, double *yrange) {
				cartesian_range_x[0] = xrange[0];
				cartesian_range_x[1] = xrange[1];
				cartesian_range_y[0] = yrange[0];
				cartesian_range_y[1] = yrange[1];
			}
			/**
			 *   get vertices
			 *
			 *   @return  vertices (std::vector) 
			 *
			 */
			vector<OSMVertex> getVertices () const {
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
							// update the ranges for lat/long and cartesian equivalent
				latitude_range[0] = 1000000.; latitude_range[1] = -1000000.;
				longitude_range[0] = 1000000.; longitude_range[1] = -1000000.;
				cartesian_range_x[0] = 1000000.; cartesian_range_x[1] = -1000000.;
				cartesian_range_y[0] = 1000000.; cartesian_range_y[1] = -1000000.;

				double lat, longit, cart_coords[2];
				for (auto& v : vertices) {
					lat = v.getLatitude();		
					longit = v.getLongitude();		
					v.getCartesianCoords(cart_coords);
					latitude_range[0] = std::min(latitude_range[0], lat);
					latitude_range[1] = std::max(latitude_range[0], lat);
					longitude_range[0] = std::min(longitude_range[1], longit);
					longitude_range[1] = std::max(longitude_range[1], longit);
					
					cartesian_range_x[0] = std::min(cartesian_range_x[0], cart_coords[0]);
					cartesian_range_x[1] = std::max(cartesian_range_x[1], cart_coords[0]);
					cartesian_range_y[0] = std::min(cartesian_range_y[0], cart_coords[1]);
					cartesian_range_y[1] = std::max(cartesian_range_y[1], cart_coords[1]);
				}
			}
			/**
			 *   get edges
			 *
			 *   @return  edges (std::vector) 
			 *
			 */
			vector<OSMEdge> getEdges () const {
				return edges;
			}
			/**
			 *   set edges
			 *
			 *   @param  edges (std::vector) 
			 *
			 */
			void setEdges (vector<OSMEdge> e) {
				edges = e;
			}
			/** 
			 * 	convert lat/long coords to Cartesian
			 *
			 */
			void toCartesianCoords(double lat, double longit, double *coords) {
				const double R = 6378.; // Radius of the earth in km
				double lat_rad  = degreeToRadians(lat);
				double longit_rad  = degreeToRadians(longit);
				coords[0] = R * cos(lat_rad) * cos (longit_rad);
				coords[1] = R * cos(lat_rad) * sin (longit_rad);
			}
	};

} // end namespace bridges

#endif
