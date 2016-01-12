#include <string>
#include <assert.h>
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

namespace Test_BSTElement
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase : Test_TreeElement::TestCase
    {
        BSTElement<KEY,TYPE>* bst;
        KEY key = KEY();
        TestCase(BSTElement<KEY,TYPE>* e) : Test_TreeElement::TestCase(e), bst(e){}
    };
    /** TestCases pertaining to this object */
    vector<TestCase*> nativeCases()
    {
        vector<TestCase*> cases;

        cases.push_back(UNIFORM_INITIALZATION(1));
        cases.back()->key = 1;

        cases.push_back(UNIFORM_INITIALZATION(2,"A"));
        cases.back()->value = "A";
        cases.back()->key = 2;

        cases.push_back(UNIFORM_INITIALZATION(3,"B","C"));
        cases.back()->value = "B";
        cases.back()->label = "C";
        cases.back()->key = 3;

        cases.push_back(UNIFORM_INITIALZATION(4,cases.back()->bst,cases.rbegin()[1]->bst));
        cases.back()->key = 4;
        cases.back()->left = cases.rbegin()[1]->bst;
        cases.back()->right = cases.rbegin()[2]->bst;

        cases.push_back(UNIFORM_INITIALZATION(5,cases.back()->bst,cases.rbegin()[1]->bst,"D"));
        cases.back()->key = 5;
        cases.back()->left = cases.rbegin()[1]->bst;
        cases.back()->right = cases.rbegin()[2]->bst;
        cases.back()->value = "D";

        cases.push_back(UNIFORM_INITIALZATION(6,cases.back()->bst,cases.rbegin()[1]->bst,"E","F"));
        cases.back()->key = 6;
        cases.back()->left = cases.rbegin()[1]->bst;
        cases.back()->right = cases.rbegin()[2]->bst;
        cases.back()->value = "E";
        cases.back()->label = "F";

        return cases;
    }

    void testGetLink(TestCase* tc)
    {
        tc->left? assert(tc->te->getLinkVisualizer(tc->left) != nullptr) : assert(tc->te->getLinkVisualizer(tc->left) == nullptr);
        tc->right? assert(tc->te->getLinkVisualizer(tc->right) != nullptr) : assert(tc->te->getLinkVisualizer(tc->right) == nullptr);
    }
    void testGetProperties(TestCase* tc)
    {
        assert(tc->bst->getKey()==tc->key);
        assert(tc->bst->getLeft()==tc->left);
        assert(tc->bst->getRight()==tc->right);
    }
    void testSetProperties(TestCase* tc)
    {
        tc->bst->setKey(tc->key = 13);
        //set to self
        tc->bst->setLeft(static_cast<BSTElement<KEY,TYPE>*>(tc->left = tc->bst));
        tc->bst->setRight(static_cast<BSTElement<KEY,TYPE>*>(tc->right = tc->bst));
        testGetChildren(tc);
        testGetLink(tc);
        //set to new value
        tc->bst->setLeft(static_cast<BSTElement<KEY,TYPE>*>(tc->left = new BSTElement<KEY,TYPE>(99)));
        tc->bst->setRight(static_cast<BSTElement<KEY,TYPE>*>(tc->right = new BSTElement<KEY,TYPE>(98)));
        testGetChildren(tc);
        testGetLink(tc);
        //set to null
        tc->bst->setLeft(static_cast<BSTElement<KEY,TYPE>*>(tc->left = nullptr));
        tc->bst->setRight(static_cast<BSTElement<KEY,TYPE>*>(tc->right = nullptr));
        testGetChildren(tc);
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
        Test_TreeElement::runTests({cases.begin(),cases.end()}); ///Inheritance tests
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}
#undef UNIFORM_INITIALZATION
#undef KEY
#undef TYPE
