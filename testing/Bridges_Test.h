#include <string>
#include <assert.h>
using namespace std;
#include "Bridges.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#ifndef KEY
    #define KEY int ///Template key parameter
#endif // KEY
#define UNIFORM_INITIALZATION(...) (new TestCase(new Bridges<KEY,TYPE>(__VA_ARGS__))) ///Syntactic Sugar

/** Namespace used to prevent naming interference with other files **/
namespace BridgesTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        Bridges<KEY,TYPE>*const bd;
        string key = "";
        string uname = "";
        int assign = 0;
        int part = 0;
        ADTVisualizer<KEY,TYPE>* vis = nullptr;
        ///Constructor - initializes constant
        TestCase(Bridges<KEY,TYPE>* e) : bd(e){}
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = UNIFORM_INITIALZATION();
        cases.push_back(tc1);

        TestCase* tc2 = UNIFORM_INITIALZATION(1,"app_id","user");
        tc2->assign = 1;
        tc2->key = "app_id";
        tc2->uname = "user";
        cases.push_back(tc2);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getBridgesObjectTest(const vector<TestCase*>&);
    void getAssignmentTest(TestCase*);
    void setAssignmentTest(TestCase*);
    void getUserNameTest(TestCase*);
    void setUserNameTest(TestCase*);
    void getKeyTest(TestCase*);
    void setKeyTest(TestCase*);
    void getVisualizerTest(TestCase*);
    void setVisualizerTest(TestCase*);
    void setElementStructureTest(TestCase*);
    void setSLelementStructureTest(TestCase*);
    void setDLelementStructureTest(TestCase*);
    void setTreeElementStructureTest(TestCase*);
    void setBSTElementStructureTest(TestCase*);
    void setGraphAdjListStructureTest(TestCase*);
    void setGraphAdjMatrixStructureTest(TestCase*);
    void visualizeTest(TestCase*);

    /** Runs Tests for all native Bridges Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all give Bridges Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        getBridgesObjectTest(cases); ///Static test, should come before non-static tests
        for(auto* tc: cases)
        {
            //getAssignmentTest(tc);
            setAssignmentTest(tc);
            //getUserNameTest(tc);
            setUserNameTest(tc);
            //getKeyTest(tc);
            setKeyTest(tc);
            getVisualizerTest(tc);
            setVisualizerTest(tc);
            //setElementStructureTest(tc);
            //setSLelementStructureTest(tc);
            //setDLelementStructureTest(tc);
            //setTreeElementStructureTest(tc);
            //setBSTElementStructureTest(tc);
            //setGraphAdjListStructureTest(tc);
            //setGraphAdjMatrixStructureTest(tc);
            //visualizeTest(tc);
        }
    }
    /** Tests getBridgesObject() correctly gets value **/
    void getBridgesObjectTest(const vector<TestCase*>& cases)
    {
        ///Should be most recently created Bridges
        assert((Bridges<KEY,TYPE>::getBridgesObject()) == cases.back()->bd);
    }
    /** Tests getAssignment() correctly gets value **/
    void getAssignmentTest(TestCase* tc)
    {
        string assign = to_string(tc->assign)+"."+(tc->part<10?"0":"")+to_string(tc->part);
        assert(tc->bd->getAssignment()==assign);
    }
    /** Tests setAssignment() correctly sets value **/
    void setAssignmentTest(TestCase* tc)
    {
        tc->part = 0; //resets with assignment
        tc->bd->setAssignment(tc->assign = 3);
        getAssignmentTest(tc);
    }
    /** Tests getUserName() correctly gets value **/
    void getUserNameTest(TestCase* tc)
    {
        assert(tc->bd->getUserName()==tc->uname);
    }
    /** Tests setUserName() correctly sets value **/
    void setUserNameTest(TestCase* tc)
    {
        tc->bd->setUserName(tc->uname = "newUser");
        getUserNameTest(tc);
    }
    /** Tests getKey() correctly gets value **/
    void getKeyTest(TestCase* tc)
    {
        assert(tc->bd->getKey()==tc->key);
    }
    /** Tests setKey() correctly gets value **/
    void setKeyTest(TestCase* tc)
    {
        tc->bd->setKey(tc->key = "newApp_id");
        getKeyTest(tc);
    }
    /** Tests getVisualizer() correctly gets value **/
    void getVisualizerTest(TestCase* tc)
    {
        assert(tc->bd->getVisualizer()==tc->vis);
    }
    /** Tests setVisualizer() correctly sets value **/
    void setVisualizerTest(TestCase* tc)
    {
        tc->bd->setVisualizer(tc->vis = new ADTVisualizer<KEY,TYPE>());
        getVisualizerTest(tc);
    }
    /** Tests setElementStructure() correctly sets value for Element **/
    void setElementStructureTest(TestCase* tc)
    {
        ///Tests 0 size fails to set Structure
        tc->bd->setDataStructure(new Element<TYPE>(),0);
        assert(tc->vis->getArraySize()!=0);

        tc->bd->setDataStructure(new Element<TYPE>(),11);
        assert(tc->vis->getArraySize()==11);
        assert(tc->vis->getVisualizerType()=="Array");
    }
    /** Tests setElementStructure() correctly sets value for SLelement **/
    void setSLelementStructureTest(TestCase* tc)
    {
        ///Test that nullptr works
        tc->bd->setDataStructure((SLelement<TYPE>*)nullptr);
        assert(tc->vis->getVisualizerType()=="llist");

        tc->bd->setDataStructure(new SLelement<TYPE>());
        assert(tc->vis->getVisualizerType()=="llist");
    }
    /** Tests setElementStructure() correctly sets value for DLelement **/
    void setDLelementStructureTest(TestCase* tc)
    {
        ///Test that nullptr works
        tc->bd->setDataStructure((DLelement<TYPE>*)nullptr);
        assert(tc->vis->getVisualizerType()=="dllist");

        tc->bd->setDataStructure(new DLelement<TYPE>());
        assert(tc->vis->getVisualizerType()=="dllist");
    }
    /** Tests setElementStructure() correctly sets value for TreeElement **/
    void setTreeElementStructureTest(TestCase* tc)
    {
        ///Test that nullptr works
        tc->bd->setDataStructure((TreeElement<TYPE>*)nullptr);
        assert(tc->vis->getVisualizerType()=="tree");

        tc->bd->setDataStructure(new TreeElement<TYPE>());
        assert(tc->vis->getVisualizerType()=="tree");
    }
    /** Tests setElementStructure() correctly sets value for BSTElement **/
    void setBSTElementStructureTest(TestCase* tc)
    {
        ///Test that nullptr works
        tc->bd->setDataStructure((BSTElement<KEY,TYPE>*)nullptr);
        assert(tc->vis->getVisualizerType()=="tree");

        tc->bd->setDataStructure(new BSTElement<KEY,TYPE>());
        assert(tc->vis->getVisualizerType()=="tree");
    }
    /** Tests setElementStructure() correctly sets value for GraphAdjList **/
    void setGraphAdjListStructureTest(TestCase* tc)
    {
        ///Test that nullptr works
        tc->bd->setDataStructure((GraphAdjList<KEY,TYPE>*)nullptr);
        assert(tc->vis->getVisualizerType()=="graphl");

        tc->bd->setDataStructure(new GraphAdjList<KEY,TYPE>());
        assert(tc->vis->getVisualizerType()=="graphl");
    }
    /** Tests setElementStructure() correctly sets value for GraphAdjMatrix **/
    void setGraphAdjMatrixStructureTest(TestCase* tc)
    {
        ///Test that nullptr works
        tc->bd->setDataStructure((GraphAdjMatrix<KEY,TYPE>*)nullptr);
        assert(tc->vis->getVisualizerType()=="graphm");

        tc->bd->setDataStructure(new GraphAdjMatrix<KEY,TYPE>());
        assert(tc->vis->getVisualizerType()=="graphm");
    }
    /** Tests visualize() correctly visualizes **/
    void visualizeTest(TestCase* tc)
    {
        for(int i=0;i<10;i++) ///10 times to verify decimal assignment works
        {
            tc->part++;
            ///Increments assigmnet part if successful, prints error if not
            tc->bd->visualize();
            ///Tests if visualize was "successful"
            getAssignmentTest(tc);
        }
    }
}
#undef UNIFORM_INITIALZATION
#undef KEY
#undef TYPE
