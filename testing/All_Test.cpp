/*#include "Color_Test.h"
    #include "LinkVisualizer_Test.h"
        #include "Element_Test.h"
            #include "SLelement_Test.h"
                #include "DLelement_Test.h"
            //#include "TreeElement_Test.h"
            #include "AVLTreeElement.h"

                //#include "BSTElement_Test.h"
        #include "GraphAdjMatrix_Test.h"
        #include "GraphAdjList_Test.h"
        #include "Bridges_Test.h"
*/
#include "Bridges.h"
#include "DLelement.h"
#include "ElementArray.h"
#include "AVLTreeElement.h"
#include "GraphAdjList.h"
#include "GraphAdjMatrix.h"
#include "DataSource.h"
using namespace bridges;
int main()
{
        //create the Bridges object
    Bridges::initialize(19,"USER_ID","API_KEY");
    DataSource::getEarthquakeData();
    //create elements
    DLelement<string> e0("","Original");
    DLelement<string> e1("","Changed");

    //link elements
    e0.setNext(&e1);
    e1.setPrev(&e0);

    //e1.setShape(DIAMOND);
    //e1.setColor(Color(0,0,255,128));
    //e1.setSize(20);

    LinkVisualizer* lv = e1.getLinkVisualizer(&e0);
    lv->setColor(Color(255,0,0,128));
    lv->setThickness(5);

    //pass first element of data structure
    Bridges::ds_handle() = &e0;

    //visualize data structure
    Bridges::visualize();

    Element<string> e("","Changed");
    e.setShape(DIAMOND);
    e.setColor(Color(0,0,0,128));
    e.setSize(20);
    Element<string> e2("","Original");
    Element<string> es[] = {e,e2};
    Bridges::setDataStructure(es,2);
    Bridges::visualize();*/
    Element<int> e(0,"\\lol");
    cout << e.getRepresentation();
    Bridges::setDataStructure(&e);
    Bridges::visualize();*/
    /*
    Test_Color::runTests();cout<<"Color Passed"<<endl;
    Test_LinkVisualizer::runTests();cout<<"LinkVisualizer Passed"<<endl;
    Test_Element::runTests();cout<<"Element Passed"<<endl;
    Test_SLelement::runTests();cout<<"SLelement Passed"<<endl;
    Test_DLelement::runTests();cout<<"DLelement Passed"<<endl;
    Test_TreeElement::runTests();cout<<"TreeElement Passed"<<endl;
    Test_BSTElement::runTests();cout<<"BSTElement Passed"<<endl;
    Test_GraphAdjMatrix::runTests();cout<<"GraphAdjMatrix Passed"<<endl;
    Test_GraphAdjList::runTests();cout<<"GraphAdjList Passed"<<endl;
    Test_Bridges::runTests();cout<<"Bridges Passed"<<endl;*/
}
