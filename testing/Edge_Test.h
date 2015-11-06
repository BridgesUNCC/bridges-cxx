#include <string>
#include <assert.h>
using namespace std;
#include "Edge.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#define UNIFORM_INITIALZATION(...) (new TestCase(new Edge<TYPE>(__VA_ARGS__))) ///Syntactic Sugar

/** Namespace used to prevent naming interference with other files **/
namespace EdgeTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        Edge<TYPE>*const ed;
        int weight = 0;
        TYPE vertex = TYPE();
        string data = "";
        ///Constructor - initializes constant
        TestCase(Edge<TYPE>* e) : ed(e){}
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = UNIFORM_INITIALZATION();
        cases.push_back(tc1);

        TestCase* tc2 = UNIFORM_INITIALZATION(3);
        tc2->weight = 3;
        cases.push_back(tc2);

        TestCase* tc3 = UNIFORM_INITIALZATION(5,"A");
        tc3->weight = 5;
        tc3->vertex = "A";
        cases.push_back(tc3);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getWeightTest(TestCase*);
    void setWeightTest(TestCase*);
    void getVertexTest(TestCase*);
    void setVertexTest(TestCase*);
    void getEdgeDataTest(TestCase*);
    void setEdgeDataTest(TestCase*);
    void getEdgeTest(TestCase*);
    void setEdgeTest(TestCase*);

    /** Runs Tests for all native Edge Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all give Edge Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            getWeightTest(tc);
            setWeightTest(tc);
            //getVertexTest(tc);
            setVertexTest(tc);
            getEdgeDataTest(tc);
            setEdgeDataTest(tc);
            getEdgeTest(tc);
            setEdgeTest(tc);
        }
    }
    /** Tests getWeight() correctly gets value **/
    void getWeightTest(TestCase* tc)
    {
        assert(tc->ed->getWeight()==tc->weight);
    }
    /** Tests setWeight() correctly sets value **/
    void setWeightTest(TestCase* tc)
    {
        tc->ed->setWeight(tc->weight = 7);
        getWeightTest(tc);
    }
    /** Tests getVertex() correctly gets value **/
    void getVertexTest(TestCase* tc)
    {
        assert(tc->ed->getVertex()==tc->vertex);
    }
    /** Tests setVertex() correctly sets value **/
    void setVertexTest(TestCase* tc)
    {
        tc->ed->setVertex(tc->vertex = "B");
        getVertexTest(tc);
    }
    /** Tests getEdgeData() correctly gets value **/
    void getEdgeDataTest(TestCase* tc)
    {
        assert(tc->ed->getEdgeData()==tc->data);
    }
    /** Tests setEdgeData() correctly sets value **/
    void setEdgeDataTest(TestCase* tc)
    {
        tc->ed->setEdgeData(tc->data = "data");
        getEdgeDataTest(tc);
    }
    /** Tests getEdge() correctly gets value **/
    void getEdgeTest(TestCase* tc)
    {
        assert(tc->ed->getEdge()==tc->ed);
    }
    /** Tests setEdge() correctly sets value **/
    void setEdgeTest(TestCase* tc)
    {
        tc->ed->setEdge(tc->weight = 11,tc->vertex = "C");
        getWeightTest(tc);
        getVertexTest(tc);
    }
}
#undef UNIFORM_INITIALZATION
#undef TYPE

