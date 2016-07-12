
#include <string>

#ifndef DATA_SOURCE_H

#define DATA_SOURCE_H 

using namespace std;

namespace bridges{

class DataSource {
	private:
		string label;

	public:
		void setLabel (string lab) {
			label = lab;
		}

		string getLabel() {
			return label;
		}
};

} // namespace bridges

#endif
		
