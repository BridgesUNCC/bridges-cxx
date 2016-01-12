#include <assert.h>
#include "SLelement.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#define UNIFORM_INITIALZATION(...) (new TestCase(new SLelement<TYPE>(__VA_ARGS__))) ///Syntactic Sugar


namespace Test_SLelement
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase: Test_Element::TestCase
    {
        SLelement<TYPE>* sl;
        SLelement<TYPE>* next = nullptr;
        TestCase(SLelement<TYPE>* e) : Test_Element::TestCase(e), sl(e){}
    };

    /** TestCases pertaining to this object */
    vector<TestCase*> nativeCases()
    {
        vector<TestCase*> cases;

        cases.push_back(UNIFORM_INITIALZATION());

        cases.push_back(UNIFORM_INITIALZATION("A"));
        cases.back()->value = "A";

        cases.push_back(UNIFORM_INITIALZATION("B","C"));
        cases.back()->value = "B";
        cases.back()->label = "C";

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->sl));
        cases.back()->next = cases.rbegin()[1]->sl;

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->sl,"D"));
        cases.back()->next = cases.rbegin()[1]->sl;
        cases.back()->value = "D";

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->sl,"E","F"));
        cases.back()->next = cases.rbegin()[1]->sl;
        cases.back()->value = "E";
        cases.back()->label = "F";

        return cases;
    }

    void testGetLink(TestCase* tc)
    {
        tc->next? assert(tc->sl->getLinkVisualizer(tc->next) != nullptr) : assert(tc->sl->getLinkVisualizer(tc->next) == nullptr);
    }
    void testGetNext(TestCase* tc)
    {
        assert(tc->sl->getNext()==tc->next);
    }
    void setNextTest(TestCase* tc)
    {
        //set to self
        tc->sl->setNext(tc->next = tc->sl);
        testGetNext(tc);
        testGetLink(tc);
        //set to new value
        tc->sl->setNext(tc->next = new SLelement<TYPE>("B","C"));
        testGetNext(tc);
        testGetLink(tc);
        //set to null
        tc->sl->setNext(tc->next = nullptr);
        testGetNext(tc);
        testGetLink(tc);
    }
    /** Runs Tests for any cases provided */
    void runTests(const vector<TestCase*>& cases)
    {
        for(TestCase* tc : cases)
        {
            testGetLink(tc);
            testGetProperties(tc);
            testSetProperties(tc);
        }
        Test_Element::runTests({cases.begin(),cases.end()}); ///Inheritance tests
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}
#undef UNIFORM_INITIALZATION
#undef TYPE
