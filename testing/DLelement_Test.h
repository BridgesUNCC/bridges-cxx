#include <string>
#include <assert.h>
using namespace std;
#include "DLelement.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#define UNIFORM_INITIALZATION(...) (new TestCase(new DLelement<TYPE>(__VA_ARGS__))) ///Syntactic Sugar

/** Namespace used to prevent naming interference with other files **/
namespace DLelementTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase : ElementTester::TestCase
    {
        ///Initializes to default value
        DLelement<TYPE>*const dl;
        DLelement<TYPE>* next = nullptr;
        DLelement<TYPE>* prev = nullptr;
        ///Constructor - calls super and initializes const
        TestCase(DLelement<TYPE>* e) : ElementTester::TestCase(e), dl(e){}
        ///Assignment Operator (Be Aware - directly copies pointer, not value at pointer)
        TestCase& operator=(const TestCase& that)
        {
            ElementTester::TestCase::operator=(that);
            next = that.next;
            prev = that.prev;
            return *this;
        }
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

        TestCase* tc3 = UNIFORM_INITIALZATION(tc1->dl,tc2->dl);
        tc3->next = tc1->dl;
        tc3->prev = tc2->dl;
        cases.push_back(tc3);

        TestCase* tc4 = UNIFORM_INITIALZATION("D",tc1->dl,tc2->dl);
        tc4->value = "D";
        tc4->next = tc1->dl;
        tc4->prev = tc2->dl;
        cases.push_back(tc4);

        TestCase* tc5 = UNIFORM_INITIALZATION(*(tc2->dl));
        *tc5 = *tc2;
        cases.push_back(tc5);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getNextTest(TestCase*);
    void getPrevTest(TestCase*);
    void setNextTest(TestCase*);
    void setPrevTest(TestCase*);

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
            getNextTest(tc);
            getPrevTest(tc);
            setNextTest(tc);
            setPrevTest(tc);
        }
        ///Inheritence Tests - Uses uniform initialization to convert to superclass
        ElementTester::runTests({cases.begin(),cases.end()});
    }
    /** Tests getNext() correctly gets value **/
    void getNextTest(TestCase* tc)
    {
        assert(tc->dl->getNext()==tc->next);
    }
    /** Tests getPrev() correctly gets value **/
    void getPrevTest(TestCase* tc)
    {
        assert(tc->dl->getPrev()==tc->prev);
    }
    /** Tests setNext() correctly sets value **/
    void setNextTest(TestCase* tc)
    {
        //set to self
        tc->dl->setNext(tc->next = tc->dl);
        getNextTest(tc);
        //set to new value
        tc->dl->setNext(tc->next = new DLelement<string>("C","B"));
        getNextTest(tc);
        //set to null
        tc->dl->setNext(tc->next = nullptr);
        getNextTest(tc);
    }
    /** Tests setPrev() correctly sets value **/
    void setPrevTest(TestCase* tc)
    {
        //set to self
        tc->dl->setPrev(tc->prev = tc->dl);
        getPrevTest(tc);
        //set to new value
        tc->dl->setPrev(tc->prev = new DLelement<TYPE>("B","C"));
        getPrevTest(tc);
        //set to null
        tc->dl->setPrev(tc->prev = nullptr);
        getPrevTest(tc);
    }
}
#undef UNIFORM_INITIALZATION
#undef TYPE
