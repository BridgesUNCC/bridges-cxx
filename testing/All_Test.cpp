#include "Color_Test.h"
    #include "LinkVisualizer_Test.h"
        #include "Element_Test.h"
            #include "SLelement_Test.h"
                #include "DLelement_Test.h"
            #include "TreeElement_Test.h"
                #include "BSTElement_Test.h"
        #include "GraphAdjMatrix_Test.h"
        #include "GraphAdjList_Test.h"
        #include "Bridges_Test.h"

using namespace bridges;
int main()
{
    Test_Color::runTests();cout<<"Color Passed"<<endl;
    Test_LinkVisualizer::runTests();cout<<"LinkVisualizer Passed"<<endl;
    Test_Element::runTests();cout<<"Element Passed"<<endl;
    Test_SLelement::runTests();cout<<"SLelement Passed"<<endl;
    Test_DLelement::runTests();cout<<"DLelement Passed"<<endl;
    Test_TreeElement::runTests();cout<<"TreeElement Passed"<<endl;
    Test_BSTElement::runTests();cout<<"BSTElement Passed"<<endl;
    Test_GraphAdjMatrix::runTests();cout<<"GraphAdjMatrix Passed"<<endl;
    Test_GraphAdjList::runTests();cout<<"GraphAdjList Passed"<<endl;
    Test_Bridges::runTests();cout<<"Bridges Passed"<<endl;
}
