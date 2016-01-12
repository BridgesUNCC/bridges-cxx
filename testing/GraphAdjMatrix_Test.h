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

namespace Test_GraphAdjMatrix
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase
    {
        GraphAdjMatrix<KEY,TYPE>* mat;
        unsigned int numVerts = 0;
        TestCase(GraphAdjMatrix<KEY,TYPE>* e) : mat(e){}
    };

    /** TestCases pertaining to this object */
    vector<TestCase*> nativeCases()
    {
        vector<TestCase*> cases;
        cases.push_back(new TestCase(new GraphAdjMatrix<KEY,TYPE>()));
        return cases;
    }

    void testGetProperties(TestCase* tc)
    {
        assert(tc->mat->getVertices().size() == tc->numVerts);

        const auto& matrix = tc->mat->getMatrix();
        assert(matrix.size() == tc->numVerts); //size of first dimention
        for(auto& j: matrix)
        {
            assert(j.second.size() == tc->numVerts); //size of each inner dimensions
        }
    }
    void testSetVertex(TestCase* tc)
    {
        //Syntactic sugar
        auto* mat = tc->mat;
        const auto& verts = mat->getVertices();
        const auto& matrix = mat->getMatrix();

        tc->numVerts+= verts.find(1)==verts.end()? 1:0;
        mat->addVertex(1,"A");
        testGetProperties(tc);
        assert(verts.at(1).getValue() == "A"); //value set correctly
        assert(matrix.at(1).at(1) == 0); //weight to self set correctly

        ///overwrite value
        mat->addVertex(1,"B");
        testGetProperties(tc);
        assert(verts.at(1).getValue() == "B");
        assert(matrix.at(1).at(1) == 0); //weight to self set correctly
    }
    void testSetEdge_and_getLink(TestCase* tc)
    {
        //Syntactic sugar
        auto* mat = tc->mat;
        const auto& verts = mat->getVertices();
        const auto& matrix = mat->getMatrix();

        //two existing verts
        tc->numVerts+= verts.find(1)==verts.end()? 1:0;
        tc->numVerts+= verts.find(2)==verts.end()? 1:0;
        mat->addVertex(1,"A");
        mat->addVertex(2,"B");

        ///new value
        mat->addEdge(1,2,13);
        testGetProperties(tc);
        assert(matrix.at(1).at(2) == 13);
        assert(matrix.at(2).at(1) == 0);//only sets one direction
        assert(verts.at(1).getLinkVisualizer(&verts.at(2))!=nullptr);
        assert(verts.at(2).getLinkVisualizer(&verts.at(1))==nullptr);

        ///overwrite value
        mat->addEdge(1,2,37);
        testGetProperties(tc);
        assert(matrix.at(1).at(2) == 37);
        assert(matrix.at(2).at(1) == 0);//only sets one direction
        assert(verts.at(1).getLinkVisualizer(&verts.at(2))!=nullptr);
        assert(verts.at(2).getLinkVisualizer(&verts.at(1))==nullptr);
    }
    /** Runs Tests for any cases provided */
    void runTests(const vector<TestCase*>& cases)
    {
        for(TestCase* tc : cases)
        {
            testGetProperties(tc);
            testSetVertex(tc);
            testSetEdge_and_getLink(tc);
        }
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}

#undef TYPE
#undef KEY

