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

/** Namespace used to prevent naming interference with other files **/
namespace GraphAdjListTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        GraphAdjList<KEY,TYPE>*const gal;
        unsigned int numVerts = 0;
        unsigned int numSrc = 0;
        unordered_map<KEY,unsigned int> numDest;
        ///Constructor - initializes constant
        TestCase(GraphAdjList<KEY,TYPE>* e) : gal(e){}
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = new TestCase(new GraphAdjList<KEY,TYPE>());
        cases.push_back(tc1);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getVerticesTest(TestCase*);
    void getAdjacencyListTest(TestCase*);
    void getKeyAdjacencyListTest(TestCase*);
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
            getVerticesTest(tc);
            getAdjacencyListTest(tc);
            getKeyAdjacencyListTest(tc); //after full get
            addVertexTest(tc); //after gets
            //addEdgeTest(tc); //after add vertex
        }
    }
    /** Tests getVertices() correctly gets value **/
    void getVerticesTest(TestCase* tc)
    {
        auto* verts = tc->gal->getVertices();
        assert(verts->size()==tc->numVerts);
    }
    /** Tests getAdjacencyList() correctly gets value **/
    void getAdjacencyListTest(TestCase* tc)
    {
        auto* adjList = tc->gal->getAdjacencyList();
        assert(adjList->size() == tc->numSrc);
    }
    /** Tests getAdjacencyList() correctly gets value for key **/
    void getKeyAdjacencyListTest(TestCase* tc)
    {
        for(auto i : *tc->gal->getAdjacencyList())
        {
            auto* slList = tc->gal->getAdjacencyList(i.first);
            assert(i.second == slList); //check getKeyList and full list at key are same
            unsigned int size = 0;
            while(slList != nullptr)
            {
                slList=slList->getNext();
                size++;
            }
            //size of each adjlist
            assert(size == tc->numDest.at(i.first));
        }
    }
    /** Tests addVertex correctly adds value **/
    void addVertexTest(TestCase* tc)
    {
        //Syntactic sugar
        auto* gal = tc->gal;
        auto* verts = gal->getVertices();
        auto* adjList = gal->getAdjacencyList();

        tc->numDest.clear();
        ///Resets graph so test knows what has and hasn't been added
        adjList->clear();
        verts->clear();

        ///new value
        gal->addVertex(1,"A");
        (tc->numVerts) = (tc->numSrc) = 1; tc->numDest[1] = 0;//updates expected sizes
        getVerticesTest(tc); getAdjacencyListTest(tc); getKeyAdjacencyListTest(tc);//checks new sizes
        assert(verts->at(1).getValue() == "A"); //value set correctly
        assert(adjList->at(1) == nullptr); //adjList initialized

        ///overwrite value
        gal->addVertex(1,"B");
        getVerticesTest(tc); getAdjacencyListTest(tc); getKeyAdjacencyListTest(tc);//checks no sizes change
        assert(verts->at(1).getValue() == "B");
        assert(adjList->at(1) == nullptr); //adjList unchanged
    }
    /** Tests addEdge() correctly adds value **/
    void addEdgeTest(TestCase* tc)
    {/*
        //Syntactic sugar
        auto* gal = tc->gal;
        auto* verts = gal->getVertices();
        auto* adjList = gal->getAdjacencyList();

        tc->numDest.clear();
        ///Resets graph so test knows what has and hasn't been added
        adjList->clear();
        verts->clear();

        //two existing verts
        gal->addVertex(1,"A");
        gal->addVertex(2,"B");

        //updates expected sizes
        (tc->numVerts) = (tc->numSrc) = 2; (tc->numDest[1]) = (tc->numDest[2]) = 0;

        ///new value
        gal->addEdge(1,2,13);
        getVerticesTest(tc); getAdjacencyListTest(tc); getKeyAdjacencyListTest(tc);//checks no sizes change
        assert(adjList->at(1)->getValue().getVertex() == 2);
        assert(adjList->at(1)->getValue().getWeight() == 13);//only sets one direction

        ///overwrite value
        gal->addEdge(1,2,37);
        assert(adjList->at(1)->getNext()==nullptr); //replaced prev value
        getVerticesTest(tc); getAdjacencyListTest(tc); getKeyAdjacencyListTest(tc);//checks no sizes change
        assert(adjList->at(1)->getValue().getVertex() == 2);
        assert(adjList->at(1)->getValue().getWeight() == 37);

        ///one non-existent vert
        gal->addEdge(1,99,13);
        tc->numDest.at(1)++;
        getVerticesTest(tc); getAdjacencyListTest(tc); getKeyAdjacencyListTest(tc);//checks new sizes
        assert(adjList->at(1)->getValue().getVertex() == 99);
        assert(adjList->at(1)->getValue().getWeight() == 13);

        ///two non-existent vert
        gal->addEdge(99,98,37);
        tc->numSrc++; tc->numDest[99]=1;
        getVerticesTest(tc); getAdjacencyListTest(tc); getKeyAdjacencyListTest(tc);//checks new sizes
        assert(adjList->at(1)->getValue().getVertex() == 98);
        assert(adjList->at(1)->getValue().getWeight() == 37);
    */}
}

#undef TYPE

