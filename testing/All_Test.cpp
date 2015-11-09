#include "Validation_Test.h"
#include "ElementVisualizer_Test.h"
#include "LinkVisualizer_Test.h"
#include "Element_Test.h"
    #include "DLelement_Test.h"
    #include "SLelement_Test.h"
    #include "TreeElement_Test.h"
        #include "BSTElement_Test.h"
#include "GraphAdjMatrix_Test.h"
#include "Edge_Test.h"
    #include "GraphAdjList_Test.h"
#include "ADTVisualizer_Test.h"
#include "Connector_Test.h"
#include "Bridges_Test.h"
int main()
{

    /** Validation - Should be first **/
    {
        ///ERROR MAKES UN-TESTABLE
        /*ValidationTester::runTests(); cout<<"Validation passed\n";*/
    }
    /** Element and Link Visualizers - Should be after Validation **/
    {
        ///VALIDATION ERROR MAKES UN-TESTABLE
        /*ElementVisualizerTester::runTests(); cout<<"ElementVisualizer passed\n"; //VALIDATION*/
        ///VALIDATION ERROR MAKES UN-TESTABLE
        ///LinkVisualizerTester::runTests(); cout<<"LinkVisualizer passed (*Except for getWeight)\n"; //VALIDATION
    }
    /** Elements - Should be after Element and LinkVisualizers **/
    {
        ElementTester::runTests(); cout<<"Element passed (*Except for JSON, Visualization, getLinkVisualization and Value Initialization)\n"; //JSON, VALIDATION
        /** Should be after Element **/
        {
            /*DLelementTester::runTests(); cout<<"DLelement passed\n"; //VALIDATION*/
            /*SLelementTester::runTests(); cout<<"SLelement passed\n"; //VALIDATION*/
            /*TreeElementTester::runTests(); cout<<"TreeElement passed\n"; //VALIDATION*/
            /** Should be after TreeElement **/
            {
                BSTElementTester::runTests(); cout<<"BSTElement passed (*Except for JSON and Key Initialization)\n"; //JSON, VALIDATION
            }
        }
    }
    /** Graphs - Should be after Elements **/
    {
        /*GraphAdjMatrixTester::runTests(); cout<<"GraphAdjMatrix passed\n"*/; //VALIDATION
        EdgeTester::runTests(); cout<<"Edge passed (*Except for Vertex Initialization)\n";
        /** Should be after Edge **/
        {
            GraphAdjListTester::runTests(); cout<<"GraphAdjList passed (*Except for addEdge)\n"; //VALIDATION
        }
    }
    /** ADTVisualizer - Should be after Graphs **/
    {
        ADTVisualizerTester::runTests(); cout<<"ADTVisualizer passed (*Except for JSON and Size Initialization)\n"; //JSON, VALIDATION
    }
    /** Connector - Should be after ADTVisualizer **/
    {
        /*ConnectorTester::runTests(); cout<<"Connector passed\n";*/
    }
    /** Bridges - Should be last **/
    {
        ///VALIDATION ERROR MAKES UN-TESTABLE
        ///BridgesTester::runTests(); cout<<"Bridges passed (*Except for visualize, setDataStructure, and Assignment, Key, and UserName Initialization)\n"; //VALIDATION
    }



}
