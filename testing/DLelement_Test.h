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

namespace Test_DLelement
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase : Test_SLelement::TestCase
    {
        DLelement<TYPE>* dl;
        DLelement<TYPE>* prev = nullptr;
        TestCase(DLelement<TYPE>* e) : Test_SLelement::TestCase(e), dl(e){}
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

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->dl));
        cases.back()->next = cases.rbegin()[1]->dl;

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->dl,cases.rbegin()[1]->dl));
        cases.back()->next = cases.rbegin()[1]->dl;
        cases.back()->prev = cases.rbegin()[2]->dl;

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->dl,cases.rbegin()[1]->dl,"D"));
        cases.back()->next = cases.rbegin()[1]->dl;
        cases.back()->prev = cases.rbegin()[2]->dl;
        cases.back()->value = "D";

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->dl,cases.rbegin()[1]->dl,"E","F"));
        cases.back()->next = cases.rbegin()[1]->dl;
        cases.back()->prev = cases.rbegin()[2]->dl;
        cases.back()->value = "E";
        cases.back()->label = "F";

        return cases;
    }

    void testGetLink(TestCase* tc)
    {
        tc->next? assert(tc->dl->getLinkVisualizer(tc->next) != nullptr) : assert(tc->dl->getLinkVisualizer(tc->next) == nullptr);
        tc->prev? assert(tc->dl->getLinkVisualizer(tc->prev) != nullptr) : assert(tc->dl->getLinkVisualizer(tc->prev) == nullptr);
    }
    void testGetNeighbors(TestCase* tc)
    {
        assert(tc->dl->getNext()==tc->next);
        assert(tc->dl->getPrev()==tc->prev);
    }
    void testSetNeighbors(TestCase* tc)
    {
        //set to self
        tc->dl->setPrev(tc->prev = tc->dl);
        tc->dl->setNext(static_cast<DLelement<TYPE>*>(tc->next = tc->dl));
        testGetNeighbors(tc);
        testGetLink(tc);
        //set to new value
        tc->dl->setNext(static_cast<DLelement<TYPE>*>(tc->next = new DLelement<TYPE>()));
        tc->dl->setPrev(tc->prev = new DLelement<TYPE>());
        testGetNeighbors(tc);
        testGetLink(tc);
        //set to null
        tc->dl->setPrev(tc->prev = nullptr);
        tc->dl->setNext(static_cast<DLelement<TYPE>*>(tc->next = nullptr));
        testGetNeighbors(tc);
        testGetLink(tc);
    }
    /** Runs Tests for any cases provided */
    void runTests(const vector<TestCase*>& cases)
    {
        for(TestCase* tc : cases)
        {
            testGetLink(tc);
            testGetProperties(tc);
            testSetNeighbors(tc);
        }
        Test_SLelement::runTests({cases.begin(),cases.end()}); ///Inheritance tests
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}
#undef UNIFORM_INITIALZATION
#undef TYPE
