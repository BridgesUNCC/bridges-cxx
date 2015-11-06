#include <string>
#include <assert.h>
using namespace std;
#include "GraphAdjMatrix.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#ifndef KEY
    #define KEY int ///Template key parameter
#endif // KEY

/** Namespace used to prevent naming interference with other files **/
namespace GraphAdjMatrixTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        GraphAdjMatrix<KEY,TYPE>*const mat;
        unsigned int numVerts = 0;
        unsigned int numSrc = 0;
        unordered_map<KEY,unsigned int> numDest;
        ///Constructor - initializes constant
        TestCase(GraphAdjMatrix<KEY,TYPE>* e) : mat(e){}
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = new TestCase(new GraphAdjMatrix<KEY,TYPE>());
        cases.push_back(tc1);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getMatrixTest(TestCase*);
    void getVerticesTest(TestCase*);
    void addVertexTest(TestCase*);
    void addEdgeTest(TestCase*);

    /** Runs Tests for all native GraphAdjMatrix Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all give GraphAdjMatrix Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            getMatrixTest(tc);
            getVerticesTest(tc);
            addVertexTest(tc); //after gets
            addEdgeTest(tc); //after add vertex
        }
    }
    /** Tests getMatrix() correctly gets value **/
    void getMatrixTest(TestCase* tc)
    {
        auto* matrix = tc->mat->getMatrix();
        assert(matrix->size() == tc->numSrc); //size of large map
        for(auto& j: *matrix)
        {
            //size of each inner map
            assert(j.second.size() == tc->numDest.at(j.first));
        }
    }
    /** Tests getVertices() correctly gets value **/
    void getVerticesTest(TestCase* tc)
    {
        auto* verts = tc->mat->getVertices();
        assert(verts->size() == tc->numVerts);
    }
    /** Tests addVertex correctly adds value **/
    void addVertexTest(TestCase* tc)
    {
        //Syntactic sugar
        auto* mat = tc->mat;
        auto* verts = mat->getVertices();
        auto* matrix = mat->getMatrix();

        tc->numDest.clear();
        ///Resets graph so test knows what has and hasn't been added
        matrix->clear();
        verts->clear();

        ///new value
        mat->addVertex(1,"A");
        (tc->numVerts) = (tc->numSrc) = (tc->numDest[1]) = 1;//updates expected sizes
        getVerticesTest(tc); getMatrixTest(tc);//checks new sizes
        assert(verts->at(1).getValue() == "A"); //value set correctly
        assert(matrix->at(1).at(1) == 0); //weight to self set correctly

        ///overwrite value
        mat->addVertex(1,"B");
        getVerticesTest(tc); getMatrixTest(tc);//checks no sizes change
        assert(verts->at(1).getValue() == "B");
        assert(matrix->at(1).at(1) == 0); //weight to self set correctly
    }
    /** Tests addEdge() correctly adds value **/
    void addEdgeTest(TestCase* tc)
    {
        //Syntactic sugar
        auto* mat = tc->mat;
        auto* verts = mat->getVertices();
        auto* matrix = mat->getMatrix();

        tc->numDest.clear();
        ///Resets graph so test knows what has and hasn't been added
        matrix->clear();
        verts->clear();

        //two existing verts
        mat->addVertex(1,"A");
        mat->addVertex(2,"B");

        //updates expected sizes
        (tc->numVerts) = (tc->numSrc) = (tc->numDest[1]) = (tc->numDest[2]) = 2;

        ///new value
        mat->addEdge(1,2,13);
        getVerticesTest(tc); getMatrixTest(tc);//checks no sizes change
        assert(matrix->at(1).at(2) == 13);
        assert(matrix->at(2).at(1) == 0);//only sets one direction

        ///overwrite value
        mat->addEdge(1,2,37);
        getVerticesTest(tc); getMatrixTest(tc);//checks no sizes change
        assert(matrix->at(1).at(2) == 37);

        ///one non-existent vert
        mat->addEdge(1,99,13);
        tc->numDest.at(1)++;
        getVerticesTest(tc); getMatrixTest(tc);//checks new sizes
        assert(matrix->at(1).at(99) == 13);

        ///two non-existent vert
        mat->addEdge(99,98,37);
        tc->numSrc++; tc->numDest[99]=1;
        getVerticesTest(tc); getMatrixTest(tc);//checks new sizes
        assert(matrix->at(99).at(98) == 37);
    }
}

#undef TYPE

