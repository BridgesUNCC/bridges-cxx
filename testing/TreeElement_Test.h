#include <string>
#include <assert.h>
using namespace std;
#include "TreeElement.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#define UNIFORM_INITIALZATION(...) (new TestCase(new TreeElement<TYPE>(__VA_ARGS__))) ///Syntactic Sugar

/** Namespace used to prevent naming interference with other files **/
namespace TreeElementTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase: ElementTester::TestCase
    {
        ///Initializes to default value
        TreeElement<TYPE>*const te;
        TreeElement<TYPE>* left = nullptr;
        TreeElement<TYPE>* right = nullptr;
        ///Constructor - calls super and initializes const
        TestCase(TreeElement<TYPE>* e) : ElementTester::TestCase(e), te(e){}
        ///Assignment Operator (Be Aware - directly copies pointer, not value at pointer)
        TestCase& operator=(const TestCase& that)
        {
            ElementTester::TestCase::operator=(that);
            left = that.left;
            right = that.right;
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
        tc2->value = "A";
        cases.push_back(tc2);

        TestCase* tc3 = UNIFORM_INITIALZATION("B","C");
        tc3->label = "B";
        tc3->value = "C";
        cases.push_back(tc3);

        TestCase* tc4 = UNIFORM_INITIALZATION(tc2->te,tc3->te);
        tc4->left = tc2->te;
        tc4->right = tc3->te;
        cases.push_back(tc4);

        TestCase* tc5 = UNIFORM_INITIALZATION("D",tc2->te,tc3->te);
        tc5->value = "D";
        tc5->left = tc2->te;
        tc5->right = tc3->te;
        cases.push_back(tc5);

        TestCase* tc6 = UNIFORM_INITIALZATION(*(tc3->te));
        *tc6 = *tc3;
        cases.push_back(tc6);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getLeftTest(TestCase*);
    void getRightTest(TestCase*);
    void setLeftTest(TestCase*);
    void setRightTest(TestCase*);

    /** Runs Tests for all native TreeElement Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all given TreeElement Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            getLeftTest(tc);
            getRightTest(tc);
            setLeftTest(tc);
            setRightTest(tc);
        }
        ///Inheritence Tests - Uses uniform initialization to convert to superclass
        ElementTester::runTests({cases.begin(),cases.end()});
    }
    /** Tests getLeft() correctly gets value **/
    void getLeftTest(TestCase* tc)
    {
        assert(tc->te->getLeft()==tc->left);
    }
    /** Tests getRight() correctly gets value **/
    void getRightTest(TestCase* tc)
    {
        assert(tc->te->getRight()==tc->right);
    }
    /** Tests setLeft() correctly sets value **/
    void setLeftTest(TestCase* tc)
    {
        //set to self
        tc->te->setLeft(tc->left = tc->te);
        getLeftTest(tc);
        //set to new value
        tc->te->setLeft(tc->left = new TreeElement<TYPE>("B","C"));
        getLeftTest(tc);
        //set to null
        tc->te->setLeft(tc->left = nullptr);
        getLeftTest(tc);
    }
    /** Tests setRight() correctly sets value **/
    void setRightTest(TestCase* tc)
    {
        //set to self
        tc->te->setRight(tc->right = tc->te);
        getRightTest(tc);
        //set to new value
        tc->te->setRight(tc->right = new TreeElement<TYPE>("B","C"));
        getRightTest(tc);
        //set to null
        tc->te->setRight(tc->right = nullptr);
        getRightTest(tc);
    }
}
#undef UNIFORM_INITIALZATION
#undef TYPE
