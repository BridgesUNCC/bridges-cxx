#include <string>
#include <assert.h>
using namespace std;
#include "BSTElement.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#ifndef KEY
    #define KEY int ///Template key parameter
#endif // KEY
#define UNIFORM_INITIALZATION(...) (new TestCase(new BSTElement<KEY,TYPE>(__VA_ARGS__))) ///Syntactic Sugar

/** Namespace used to prevent naming interference with other files **/
namespace BSTElementTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase : TreeElementTester::TestCase
    {
        ///Initializes to default value
        BSTElement<KEY,TYPE>*const bst;
        KEY key = KEY();
        //Left and Right pointers are taken care of by super-class
        ///Constructor - calls super and initializes const
        TestCase(BSTElement<KEY,TYPE>* e) : TreeElementTester::TestCase(e), bst(e){}
        ///Assignment Operator
        TestCase& operator=(const TestCase& that)
        {
            TreeElementTester::TestCase::operator=(that);
            key = that.key;
            return *this;
        }
    };
    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = UNIFORM_INITIALZATION();
        cases.push_back(tc1);

        TestCase* tc2 = UNIFORM_INITIALZATION("A");
        tc2->value="A";
        cases.push_back(tc2);

        TestCase* tc3 = UNIFORM_INITIALZATION(3,"B");
        tc3->key = 3;
        tc3->value="B";
        cases.push_back(tc3);

        TestCase* tc4 = UNIFORM_INITIALZATION("C",5,"D");
        tc4->label="C";
        tc4->key = 5;
        tc4->value="D";
        cases.push_back(tc4);

        TestCase* tc5 = UNIFORM_INITIALZATION(tc3->bst,tc4->bst);
        tc5->left = tc3->bst;
        tc5->right = tc4->bst;
        cases.push_back(tc5);

        TestCase* tc6 = UNIFORM_INITIALZATION("E",tc4->bst,tc5->bst);
        tc6->value="E";
        tc6->left = tc4->bst;
        tc6->right = tc5->bst;
        cases.push_back(tc6);

        TestCase* tc7 = UNIFORM_INITIALZATION(7,"F",tc5->bst,tc6->bst);
        tc7->key = 7;
        tc7->value="F";
        tc7->left = tc5->bst;
        tc7->right = tc6->bst;
        cases.push_back(tc7);

        TestCase* tc8 = UNIFORM_INITIALZATION(*(tc3->bst));
        *tc8 = *tc3;
        cases.push_back(tc8);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getKeyTest(TestCase*);
    void setKeyTest(TestCase*);
    void getLeftTest(TestCase*);
    void getRightTest(TestCase*);
    void getRepresentationTest(TestCase*);

    /** Runs Tests for all native BSTElement Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all given BSTElement Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            //getKeyTest(tc);
            setKeyTest(tc);
            getLeftTest(tc);
            getRightTest(tc);
            //getRepresentationTest(tc);
        }
        ///Inheritence Tests - Uses uniform initialization to convert to superclass
        TreeElementTester::runTests({cases.begin(),cases.end()});
    }
    /** Tests getKey() correctly gets value **/
    void getKeyTest(TestCase* tc)
    {
        assert(tc->bst->getKey()==tc->key);
    }
    /** Tests setKey() correctly sets value **/
    void setKeyTest(TestCase* tc)
    {
        tc->bst->setKey(tc->key = 13);
        getKeyTest(tc);
    }
    /** Tests getLeft() correctly gets value **/
    void getLeftTest(TestCase* tc)
    {
        assert(tc->bst->getLeft()==tc->left);
    }
    /** Tests getRight() correctly gets value **/
    void getRightTest(TestCase* tc)
    {
        assert(tc->bst->getRight()==tc->right);
    }
    /** Tests getRepresentation() gets JSON **/
    void getRepresentationTest(TestCase* tc)
    {

    }
}
#undef UNIFORM_INITIALZATION
#undef KEY
#undef TYPE
