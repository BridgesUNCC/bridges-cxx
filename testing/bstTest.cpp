#include "BSTElement.h"
#include "Bridges.h"
#include "data_src_dependent/EarthquakeUSGS.h"
#include "connect/DataFormatter.h"

using namespace bridges;

int main() {
	//create the Bridges object
	Bridges::initialize(19,"USER_ID","API_KEY");

	DataFormatter *dfm = new DataFormatter;

	vector<EarthquakeUSGS> *eq = dfm->getUSGSEarthquakeData(5);
    
    //create elements
    BSTElement<float ,string> e0((*eq)[0].getMagnitude(),"20","Hi");
    BSTElement<float ,string> e1((*eq)[1].getMagnitude(),"10","Hello");
    BSTElement<float ,string> e2((*eq)[2].getMagnitude(), "30","World");
    BSTElement<float ,string> e3((*eq)[3].getMagnitude(), "40","World");

	for (int k = 0; k < 3; k++)
		cout << "Magn:" << (*eq)[k].getMagnitude() << endl;
    
    //link elements
    e0.setLeft(&e1);
    e0.setRight(&e2);
	e2.setRight(&e3);

	Color c = e0.getVisualizer()->getColor();
	e0.getVisualizer()->setColor("magenta");
    
cout << "rgba:" << c.getRed() << "," << c.getGreen() << ","
		<< c.getBlue() << "," << c.getAlpha() << endl;
    //pass first element of data structure
    Bridges::setDataStructure(&e0);

cout << "Magn(driver):" << e0.getKey() << endl;
cout << "Magn(driver):" << e0.getLeft()->getKey() << endl;
cout << "Magn(driver):" << e0.getRight()->getKey() << endl;
cout << "Magn(driver):" << e0.getRight()->getRight()->getKey() << endl;

	Bridges::setVisualizeJSON(true);
    
    //visualize data structure
	Bridges::visualize();
}
