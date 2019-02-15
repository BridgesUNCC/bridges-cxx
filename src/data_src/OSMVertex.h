#ifndef OSM_VERTEX_H

#define OSM_VERTEX_H

#include <string>
#include <cmath>

using namespace std;

namespace bridges {
	/**
	 * @brief  Class that hold Open Street Map vertices
	 *
	 * Class that holds Open Street Map vertices from https://openstreetmap.org
	 *
	 * Kalpathi Subramanian, 2/14/19
	 *
	 */


	class OSMVertex {

		private:
			double latitude;		// latitude 
			double longitude;		// longitude

			double degreeToRadians(double deg) {
				return deg*M_PI/180.;
			}
		public:

			OSMVertex() : latitude(0.0), longitude(0.0) {
			}

			OSMVertex (double latit, double longit) 
				: latitude(latit), longitude(longit) {
			}

			OSMVertex(const OSMVertex *vert)
				: latitude(vert->latitude), longitude(vert->longitude){
			}

			/**
			 *	get latitude  of node
			 *
			 *	@return double
			 *
			 */
			double getLatitude() const {
				return latitude;
			}
			/**
			 *	set latitude of quake location
			 *
			 *	@param latit latitude of node
			 *
			 */
			void setLatitude(double latit) {
				latitude = latit;
			}
			/**
			 *	get longitude of quake location
			 *
			 *	@return longitude of node
			 *
			 */
			double getLongitude() const {
				return longitude;
			}
			/**
			 *	set longitude of quake location
			 *
			 *	@param (double)
			 *
			 */
			void setLongitude(double longit) {
				this->longitude = longit;
			}
			/** 
			 * 	convert lat/long coords to Cartesian
			 *
			 */
			void getCartesianCoords(double *cartesian_coords) {
				double R = 6378.; // Radius of the earth in km
				double lat_rad  = degreeToRadians(latitude);
				double longit_rad  = degreeToRadians(longitude);
				cartesian_coords[0] = R * cos(lat_rad) * cos (longit_rad);
				cartesian_coords[1] = R * cos(lat_rad) * sin (longit_rad);
			}
	};

} // namespace bridges

#endif
