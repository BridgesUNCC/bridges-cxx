#ifndef OSM_DATA

#define OSM_DATA

#include <math.h>
#include <cmath>


#include <algorithm>

//should be defined in math.h but VS2017 has a weird behavior here.
#ifndef M_PI
#define M_PI 3.1415926535897
#endif


#include <GraphAdjList.h>

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

			bool debug() const {
				return false;
			}

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
				return deg * M_PI / 180.;
			}

		public:


			/**
			 * Construct a graph out of the vertex and edge
			 * data of the OSM object.  The graph will
			 * associate the length of the edge to the
			 * graph edge. No data is bound to the
			 * vertices.
			 *
			 * The vertices of the graph will be located at
			 * the location given in the data set
			 * converted to cartesian coordinate.
			 **/
			void getGraph (GraphAdjList<int, OSMVertex, double>* gr) const {
				//	vector<OSMVertex> vertices = osm_data->getVertices();
				//	vector<OSMEdge> edges = osm_data->getEdges();

				int k = 0;
				double coords[2];

				double xrange[2], yrange[2];
				this->getCartesianCoordsRange(xrange, yrange);
				if (debug()) {
					cout << "Range(Cartesian):" << xrange[0] << "," << xrange[1] <<
						yrange[0] << "," << yrange[1] << endl;
				}


				double ll[2], ur[2];
				// translation
				double tx  = xrange[0];
				double ty  = yrange[0];

				// scale factor -- assume  a display of 1000 pixels wide
				double sx = 1000. / (xrange[1] - xrange[0]);
				double sy = 1000. / (yrange[1] - yrange[0]);

				if (debug()) {
					cout << "Translate:" << tx << "," << ty << endl;
					cout << "Scale:" << sx << "," << sy << endl;
				}

				k = 0;
				for (int k = 0; k < vertices.size(); k++) {
					gr->addVertex(k, vertices[k]);
					vertices[k].getCartesianCoords(coords);
					//coords[1] = yrange[1] - (coords[1] - yrange[0]);
					//double x = (coords[0]-tx)*sx, y = (coords[1]-ty)*sy;
					double x = coords[0];
					double y = coords[1];
					gr->getVertex(k)->getVisualizer()->setLocation( x, y);
					gr->getVertex(k)->getVisualizer()->setColor(Color("green"));
				}
				for (int k = 0; k < edges.size(); k++) {
					//	  std::cout<<edges[k].getEdgeLength()<<std::endl;

					gr->addEdge(edges[k].getSourceVertex(), edges[k].getDestinationVertex(),
						edges[k].getEdgeLength() );
				}

				if (debug()) {
					cout << "Num vertices, Edges: " << vertices.size() << "," << edges.size() << endl;
				}

			}


			OSMData() {
			}

			/**
			 *   get the name of the dataset
			 *
			 *   @return  name (string)
			 *
			 */
			const string& getName() const {
				return name;
			}
			/**
			 *   get the name of the dataset
			 *
			 *   @param  name (string)
			 *
			 */
			void setName(const string& n) {
				name = n;
			}

			/**
			 *   get the Latitude and Longitude range of the dataset
			 *
			 *   @param  lat_range
			 *   @param  longit_range
			 *	 @return none
			 */
			void getLatLongRange (double *lat_range, double *longit_range) const {
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
			void getCartesianCoordsRange (double *xrange, double *yrange) const {
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
			const vector<OSMVertex>& getVertices () const {
				return vertices;
			}
			/**
			 *   set vertices
			 *
			 *   @param  vertices (std::vector)
			 *
			 */
			void setVertices (const vector<OSMVertex>& verts) {
				vertices = verts;
				// update the ranges for lat/long and cartesian equivalent
				latitude_range[0] = 1000000.;
				latitude_range[1] = -1000000.;
				longitude_range[0] = 1000000.;
				longitude_range[1] = -1000000.;
				cartesian_range_x[0] = 1000000.;
				cartesian_range_x[1] = -1000000.;
				cartesian_range_y[0] = 1000000.;
				cartesian_range_y[1] = -1000000.;

				double lat, longit, cart_coords[2];
				for (auto& v : vertices) {
					lat = v.getLatitude();
					longit = v.getLongitude();
					v.getCartesianCoords(cart_coords);
					latitude_range[0] = (std::min)(latitude_range[0], lat); //The parenthesis around std::min are needed to workaround a VS2017 bug

					latitude_range[1] = (std::max)(latitude_range[0], lat);
					longitude_range[0] = (std::min)(longitude_range[1], longit);
					longitude_range[1] = (std::max)(longitude_range[1], longit);

					cartesian_range_x[0] = (std::min)(cartesian_range_x[0], cart_coords[0]);
					cartesian_range_x[1] = (std::max)(cartesian_range_x[1], cart_coords[0]);
					cartesian_range_y[0] = (std::min)(cartesian_range_y[0], cart_coords[1]);
					cartesian_range_y[1] = (std::max)(cartesian_range_y[1], cart_coords[1]);
				}
			}
			/**
			 *   get edges
			 *
			 *   @return  edges (std::vector)
			 *
			 */
			const vector<OSMEdge>& getEdges () const {
				return edges;
			}
			/**
			 *   set edges
			 *
			 *   @param  edges (std::vector)
			 *
			 */
			void setEdges (const vector<OSMEdge>& e) {
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
