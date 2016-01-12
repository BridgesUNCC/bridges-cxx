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

namespace Test_TreeElement
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase: Test_Element::TestCase
    {
        TreeElement<TYPE>* te;
        TreeElement<TYPE>* left = nullptr;
        TreeElement<TYPE>* right = nullptr;
        TestCase(TreeElement<TYPE>* e) : Test_Element::TestCase(e), te(e){}
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

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->te,cases.rbegin()[1]->te));
        cases.back()->left = cases.rbegin()[1]->te;
        cases.back()->right = cases.rbegin()[2]->te;

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->te,cases.rbegin()[1]->te,"D"));
        cases.back()->left = cases.rbegin()[1]->te;
        cases.back()->right = cases.rbegin()[2]->te;
        cases.back()->value = "D";

        cases.push_back(UNIFORM_INITIALZATION(cases.back()->te,cases.rbegin()[1]->te,"E","F"));
        cases.back()->left = cases.rbegin()[1]->te;
        cases.back()->right = cases.rbegin()[2]->te;
        cases.back()->value = "E";
        cases.back()->label = "F";

        return cases;
    }

    void testGetLink(TestCase* tc)
    {
        tc->left? assert(tc->te->getLinkVisualizer(tc->left) != nullptr) : assert(tc->te->getLinkVisualizer(tc->left) == nullptr);
        tc->right? assert(tc->te->getLinkVisualizer(tc->right) != nullptr) : assert(tc->te->getLinkVisualizer(tc->right) == nullptr);
    }
    void testGetChildren(TestCase* tc)
    {
        assert(tc->te->getLeft()==tc->left);
        assert(tc->te->getRight()==tc->right);
    }
    void testSetChildren(TestCase* tc)
    {
        //set to self
        tc->te->setLeft(tc->left = tc->te);
        tc->te->setRight(tc->right = tc->te);
        testGetChildren(tc);
        testGetLink(tc);
        //set to new value
        tc->te->setLeft(tc->left = new TreeElement<TYPE>());
        tc->te->setRight(tc->right = new TreeElement<TYPE>());
        testGetChildren(tc);
        testGetLink(tc);
        //set to null
        tc->te->setLeft(tc->left = nullptr);
        tc->te->setRight(tc->right = nullptr);
        testGetChildren(tc);
        testGetLink(tc);
    }
    /** Runs Tests for any cases provided */
    void runTests(const vector<TestCase*>& cases)
    {
        for(TestCase* tc : cases)
        {
            testGetLink(tc);
            testGetChildren(tc);
            testSetChildren(tc);
        }
        Test_Element::runTests({cases.begin(),cases.end()}); ///Inheritance tests
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}
#undef UNIFORM_INITIALZATION
#undef TYPE
