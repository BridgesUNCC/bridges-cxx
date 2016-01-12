#include <assert.h>
#include "LinkVisualizer.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#define UNIFORM_INITIALZATION(...) (new TestCase(new LinkVisualizer(__VA_ARGS__))) ///Syntactic Sugar

namespace Test_LinkVisualizer
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase
    {
        LinkVisualizer* lvis;
        double thick = LinkVisualizer::DEFAULT_THICKNESS;
        Color color = LinkVisualizer::DEFAULT_COLOR;
        TestCase(LinkVisualizer* e) : lvis(e){}
    };

    /** TestCases pertaining to this object */
    vector<TestCase*> nativeCases()
    {
        vector<TestCase*> cases;

        cases.push_back(UNIFORM_INITIALZATION());

        cases.push_back(UNIFORM_INITIALZATION(Color("red")));
        cases.back()->color = Color("red");

        cases.push_back(UNIFORM_INITIALZATION(Color("green"),5.1));
        cases.back()->color = Color("green");
        cases.back()->thick = 5.1;

        return cases;
    }

    void testGetProperties(TestCase* tc)
    {
        assert(tc->lvis->getColor()==tc->color);
        assert(tc->lvis->getThickness()==tc->thick);
    }
    void testSetProperties(TestCase* tc)
    {
        tc->lvis->setThickness(tc->thick = 7.3);
        tc->lvis->setColor(tc->color = Color("blue"));
        testGetProperties(tc);
    }
    /** Runs Tests for any cases provided */
    void runTests(const vector<TestCase*>& cases)
    {
        for(TestCase* tc : cases)
        {
            testGetProperties(tc);
            testSetProperties(tc);
        }
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}
#undef UNIFORM_INITIALZATION
