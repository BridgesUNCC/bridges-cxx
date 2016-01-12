#include <assert.h>
#include "Element.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#define UNIFORM_INITIALZATION(...) (new TestCase(new Element<TYPE>(__VA_ARGS__))) ///Syntactic Sugar

namespace Test_Element
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase
    {
        Element<TYPE>* ele;
        Color color = Element<TYPE>::DEFAULT_COLOR;
        Shape shape = Element<TYPE>::DEFAULT_SHAPE;
        double size = Element<TYPE>::DEFAULT_SIZE;
        string label;
        TYPE value = TYPE();
        TestCase(Element<TYPE>* e) : ele(e){}
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

        return cases;
    }

    void testGetLink(TestCase* tc)
    {
        assert(tc->ele->getLinkVisualizer(new Element<TYPE>)==nullptr);
    }
    void testGetProperties(TestCase* tc)
    {
        assert(tc->ele->getLabel()==tc->label);
        assert(tc->ele->getValue()==tc->value);
        assert(tc->ele->getColor()==tc->color);
        assert(tc->ele->getShape()==tc->shape);
        assert(tc->ele->getSize()==tc->size);
    }
    void testSetProperties(TestCase* tc)
    {
        tc->ele->setLabel(tc->label = "X");
        tc->ele->setValue(tc->value = "Y");
        tc->ele->setColor(tc->color = Color("brown"));
        tc->ele->setShape(tc->shape = TRI_UP);
        tc->ele->setSize(tc->size = 14.3);
        testGetProperties(tc);
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
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}
#undef UNIFORM_INITIALZATION
#undef TYPE

