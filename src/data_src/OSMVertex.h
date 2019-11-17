#ifndef OSM_VERTEX_H

#define OSM_VERTEX_H

#include <string>
#include <cmath>
#include <math.h>

//workaround a VS2017 idiosyncracies
#ifndef M_PI
#define M_PI 3.1415926535897
#endif


using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 * @brief  Class that hold Open Street Map vertices
		 *
		 * Class that holds Open Street Map vertices from https://openstreetmap.org
		 *
		 * @author Kalpathi Subramanian
		 * @date 2/14/19
		 *
		 */
		class OSMVertex {
		public:
		  typedef long OSMVertexID;
		  
			private:
		  OSMVertexID id;
				double latitude = 0.0;		// latitude
				double longitude = 0.0;		// longitude

				double cartesian_coords[2] = {0.0, 0.0};
				/**
				 * 	convert lat/long coords to Cartesian
				 *
				 */
				void toCartesianCoords() {
					const double R = 6378.; // Radius of the earth in km
					double lat_rad  = latitude * M_PI / 180.;
					double longit_rad  = longitude * M_PI / 180.;
					cartesian_coords[0] = R * cos(lat_rad) * cos (longit_rad);
					cartesian_coords[1] = R * cos(lat_rad) * sin (longit_rad);
				}

			public:

				OSMVertex() {
				}

		  OSMVertex (OSMVertexID vid, double latit, double longit)
		    : id(vid), latitude(latit), longitude(longit) {

					toCartesianCoords ();
				}

				OSMVertex(const OSMVertex *vert)
					: latitude(vert->latitude), longitude(vert->longitude) {
				}

				/**
				 *	get latitude  of node
				 *
				 *	@return latitude of the vertex
				 */
				double getLatitude() const {
					return latitude;
				}
				/**
				 *	set latitude of quake location
				 *
				 *	@param latit latitude of node
				 */
				void setLatitude(double latit) {
					latitude = latit;
					toCartesianCoords();
				}
				/**
				 *	get longitude of vertex
				 *
				 *	@return longitude of node
				 */
				double getLongitude() const {
					return longitude;
				}
				/**
				 *	set longitude of  vertex
				 *
				 *	@param longit longitude
				 */
				void setLongitude(double longit) {
					this->longitude = longit;
					toCartesianCoords();
				}

				/**
				 * 	get Cartesian coords of lat/long
				 *
				 *	@param[out] coords cartesian coordinate coords[0] is x, coords[1] is y
				 */
				void getCartesianCoords(double *coords) const {
					coords[0] = cartesian_coords[0];
					coords[1] = cartesian_coords[1];
				}
		  void setVertexID(OSMVertexID vid) {
		    this->id = vid;
		  }
		  OSMVertexID getVertexID() const {
		    return this->id;
		  }
		};
	}
} // namespace bridges

#endif
