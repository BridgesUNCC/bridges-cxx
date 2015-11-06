#include <string>
#include <vector>
#include <assert.h>
using namespace std;
#include "SLelement.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#define UNIFORM_INITIALZATION(...) (new TestCase(new SLelement<TYPE>(__VA_ARGS__))) ///Syntactic Sugar


/** Namespace used to prevent naming interference with other files **/
namespace SLelementTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase: ElementTester::TestCase
    {
        ///Initializes to default value
        SLelement<TYPE>*const sl;
        SLelement<TYPE>* next = nullptr;
        ///Constructor - calls super and initializes const
        TestCase(SLelement<TYPE>* e) : ElementTester::TestCase(e), sl(e){}
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = UNIFORM_INITIALZATION();
        cases.push_back(tc1);

        TestCase* tc2 = UNIFORM_INITIALZATION("A","B");
        tc2->label = "A";
        tc2->value = "B";
        cases.push_back(tc2);

        TestCase* tc3 = UNIFORM_INITIALZATION("C",tc2->sl);
        tc3->value = "C";
        tc3->next = tc2->sl;
        cases.push_back(tc3);

        TestCase* tc4 = UNIFORM_INITIALZATION(tc3->sl);
        tc4->next = tc3->sl;
        cases.push_back(tc4);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getNextTest(TestCase*);
    void setNextTest(TestCase*);

    /** Runs Tests for all native SLelement Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all given SLelement Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            getNextTest(tc);
            setNextTest(tc);
        }
        ///Inheritence Tests - Uses uniform initialization to convert to superclass
        ElementTester::runTests({cases.begin(),cases.end()});
    }
    /** Tests getNext() correctly gets value **/
    void getNextTest(TestCase* tc)
    {
        assert(tc->sl->getNext()==tc->next);
    }
    /** Tests setNext() correctly sets value **/
    void setNextTest(TestCase* tc)
    {
        //set to self
        tc->sl->setNext(tc->next = tc->sl);
        getNextTest(tc);
        //set to new value
        tc->sl->setNext(tc->next = new SLelement<TYPE>("B","C"));
        getNextTest(tc);
        //set to null
        tc->sl->setNext(tc->next = nullptr);
        getNextTest(tc);
    }
}
#undef UNIFORM_INITIALZATION
#undef TYPE
