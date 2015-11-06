#include <string>
#include <assert.h>
using namespace std;
#include "ADTVisualizer.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#define KEY int ///Template key parameter
#define TYPE string ///Template type parameter

/** Namespace used to prevent naming interference with other files **/
namespace ADTVisualizerTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        ADTVisualizer<KEY,TYPE>*const adt;
        bool visFlag = false;
        string visType = "";
        int size = 0;
        ///Constructor - initializes constant
        TestCase(ADTVisualizer<KEY,TYPE>* e) : adt(e){}
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = new TestCase(new ADTVisualizer<KEY,TYPE>());
        cases.push_back(tc1);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void isVisualizeJSONTest(TestCase*);
    void setVisualizerJSONTest(TestCase*);
    void getVisualizerTypeTest(TestCase*);
    void setVisualizerTypeTest(TestCase*);
    void getArraySizeTest(TestCase*);
    void setArraySizeTest(TestCase*);
    void getElementRepresentationTest(TestCase*);
    void getTreeElementRepresentationTest(TestCase*);
    void getBSTElementRepresentationTest(TestCase*);
    void getSLelementRepresentationTest(TestCase*);
    void getDLelementRepresentationTest(TestCase*);
    void getGraphAdjMatrixRepresentationTest(TestCase*);
    void getGraphAdjListRepresentationTest(TestCase*);

    /** Runs Tests for all native ADTVisualizer Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all give ADTVisualizer Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            isVisualizeJSONTest(tc);
            setVisualizerJSONTest(tc);
            getVisualizerTypeTest(tc);
            setVisualizerTypeTest(tc);
            //getArraySizeTest(tc);
            setArraySizeTest(tc);
            //getGraphAdjMatrixRepresentationTest(tc);
            //getGraphAdjListRepresentationTest(tc);
            //getSLelementRepresentationTest(tc);
            //getDLelementRepresentationTest(tc);
            //getElementRepresentationTest(tc);
            //getTreeElementRepresentationTest(tc);
            //getBSTElementRepresentationTest(tc);
        }
    }
    /** Tests isVisualizeJSON() correctly gets value **/
    void isVisualizeJSONTest(TestCase* tc)
    {
        assert(tc->adt->isVisualizeJSON()==tc->visFlag);
    }
    /** Tests setVisualizeJSON() correctly sets value **/
    void setVisualizerJSONTest(TestCase* tc)
    {
        tc->adt->setVisualizeJSON(tc->visFlag = true);
        isVisualizeJSONTest(tc);
    }
    /** Tests getVisualizerType() correctly gets value **/
    void getVisualizerTypeTest(TestCase* tc)
    {
        assert(tc->adt->getVisualizerType()==tc->visType);
    }
    /** Tests setVisualizerType() correctly sets value **/
    void setVisualizerTypeTest(TestCase* tc)
    {
        tc->visType = "llist";
        tc->adt->setVisualizerType("Array_Stack");
        getVisualizerTypeTest(tc);
    }
    /** Tests getArraySize() correctly gets value **/
    void getArraySizeTest(TestCase* tc)
    {
        assert(tc->adt->getArraySize()==tc->size);
    }
    /** Tests setArraySize() correctly sets value **/
    void setArraySizeTest(TestCase* tc)
    {
        tc->adt->setArraySize(tc->size = 20);
        getArraySizeTest(tc);
    }
    /** Tests getDataStructure() gets JSON for GraphAdjMatrix **/
    void getGraphAdjMatrixRepresentationTest(TestCase* tc)
    {

    }
    /** Tests getDataStructure() gets JSON for GraphAdjList **/
    void getGraphAdjListRepresentationTest(TestCase* tc)
    {

    }
    /** Tests getDataStructure() gets JSON for SLelement **/
    void getSLelementRepresentationTest(TestCase* tc)
    {

    }
    /** Tests getDataStructure() gets JSON for DLelement **/
    void getDLelementRepresentationTest(TestCase* tc)
    {

    }/** Tests getDataStructure() gets JSON for Element **/
    void getElementRepresentationTest(TestCase* tc)
    {

    }
    /** Tests getDataStructure() gets JSON for TreeElement **/
    void getTreeElementRepresentationTest(TestCase* tc)
    {

    }
    /** Tests getDataStructure() gets JSON for BSTElement **/
    void getBSTElementRepresentationTest(TestCase* tc)
    {

    }
}
#undef TYPE
#undef KEY
