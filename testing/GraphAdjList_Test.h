#include <string>
#include <assert.h>
using namespace std;
#include "GraphAdjList.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#ifndef KEY
    #define KEY int ///Template key parameter
#endif // KEY

namespace Test_GraphAdjList
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase
    {
        GraphAdjList<KEY,TYPE>* gal;
        unsigned int numVerts = 0;
        unordered_map<KEY,unsigned int> numDest;
        TestCase(GraphAdjList<KEY,TYPE>* e) : gal(e){}
    };

    /** TestCases pertaining to this object */
    vector<TestCase*> nativeCases()
    {
        vector<TestCase*> cases;
        cases.push_back(new TestCase(new GraphAdjList<KEY,TYPE>()));
        return cases;
    }

    void testGetProperties(TestCase* tc)
    {
        assert(tc->gal->getVertices().size()==tc->numVerts);

        const auto& adjList = tc->gal->getAdjacencyList();
        assert(adjList.size() == tc->numVerts);

        for(auto i : adjList)
        {
            assert(i.second == tc->gal->getAdjacencyList(i.first)); //check getKeyList and full list at key are same
        }
    }
    void testSetVertex(TestCase* tc)
    {
        //Syntactic sugar
        auto* gal = tc->gal;
        const auto& verts = gal->getVertices();
        const auto& adjList = gal->getAdjacencyList();

        tc->numVerts+= verts.find(1)==verts.end()? 1:0;
        gal->addVertex(1,"A");
        testGetProperties(tc);//checks new sizes
        assert(verts.at(1).getValue() == "A"); //value set correctly
        assert(adjList.at(1) == nullptr); //adjList cleared/initialized

        ///overwrite value
        gal->addVertex(1,"B");
        testGetProperties(tc);//checks no sizes change
        assert(verts.at(1).getValue() == "B");
        assert(adjList.at(1) == nullptr); //adjList cleared
    }
    void testSetEdge_and_getLink(TestCase* tc)
    {
        //Syntactic sugar
        auto* gal = tc->gal;
        const auto& verts = gal->getVertices();
        const auto& adjList = gal->getAdjacencyList();

        //two existing verts
        tc->numVerts+= verts.find(1)==verts.end()? 1:0;
        tc->numVerts+= verts.find(2)==verts.end()? 1:0;
        gal->addVertex(1,"A");
        gal->addVertex(2,"B");

        ///new value
        gal->addEdge(1,2,13);
        testGetProperties(tc);
        auto* slList = adjList.at(1);
        while(slList && slList->getValue().getVertex() != 2)
        {
            slList = slList->getNext();
        }
        assert(slList != nullptr); //found value
        assert(slList->getValue().getWeight() == 13);
        assert(verts.at(1).getLinkVisualizer(&verts.at(2))!=nullptr);
        assert(verts.at(2).getLinkVisualizer(&verts.at(1))==nullptr);

        ///overwrite value
        gal->addEdge(1,2,37,"data");
        testGetProperties(tc);
        slList = adjList.at(1);
        while(slList && slList->getValue().getVertex() != 2)
        {
            slList = slList->getNext();
        }
        assert(slList != nullptr); //found value
        assert(slList->getValue().getWeight() == 37);
        assert(slList->getValue().getEdgeData() == "data");
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

