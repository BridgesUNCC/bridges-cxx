#include <string>
#include <assert.h>
using namespace std;
#include "LinkVisualizer.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#define UNIFORM_INITIALZATION(...) (new TestCase(new LinkVisualizer(__VA_ARGS__))) ///Syntactic Sugar

/** Namespace used to prevent naming interference with other files **/
namespace LinkVisualizerTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        LinkVisualizer*const lvis;
        double thick = 1.0;
        string color = "black";
        double opac = 1.0;
        double weight = 0.0;
        ///Constructor - initializes constant
        TestCase(LinkVisualizer* e) : lvis(e){}
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = UNIFORM_INITIALZATION();
        cases.push_back(tc1);

        TestCase* tc2 = UNIFORM_INITIALZATION("red",0.5,5.0);
        tc2->color = "red";
        tc2->opac = 0.5;
        tc2->thick = 5.0;
        cases.push_back(tc2);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getThicknessTest(TestCase*);
    void setThicknessTest(TestCase*);
    void getColorTest(TestCase*);
    void setColorTest(TestCase*);
    void getOpacityTest(TestCase*);
    void setOpacityTest(TestCase*);
    void getWeightTest(TestCase*);
    void setWeightTest(TestCase*);
    void getPropertiesTest(TestCase*);

    /** Runs Tests for all native ElementVisualizer Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all give ElementVisualizer Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            getThicknessTest(tc);
            setThicknessTest(tc);
            getColorTest(tc);
            setColorTest(tc);
            getOpacityTest(tc);
            setOpacityTest(tc);
            //getWeightTest(tc);
            setWeightTest(tc);
            getPropertiesTest(tc);
        }
    }
    /** Tests getThickness() correctly gets value **/
    void getThicknessTest(TestCase* tc)
    {
        assert(tc->lvis->getThickness()==tc->thick);
    }
    /** Tests setThickness() correctly sets value **/
    void setThicknessTest(TestCase* tc)
    {
        tc->lvis->setThickness(tc->thick = 13.0);
        getThicknessTest(tc);
    }
    /** Tests getColor() correctly gets value **/
    void getColorTest(TestCase* tc)
    {
        assert(tc->lvis->getColor()==tc->color);
    }
    /** Tests setColor() correctly sets value **/
    void setColorTest(TestCase* tc)
    {
        tc->lvis->setColor(tc->color = "green"); //only lower case
        getColorTest(tc);

        tc->lvis->setColor(tc->color = "BrOwN"); //contains upper case
        getColorTest(tc);
    }
    /** Tests getOpacity() correctly gets value **/
    void getOpacityTest(TestCase* tc)
    {
        assert(tc->lvis->getOpacity()==tc->opac);
    }
    /** Tests setOpacity() correctly sets value **/
    void setOpacityTest(TestCase* tc)
    {
        tc->lvis->setOpacity(tc->opac = 0.3);
        getOpacityTest(tc);
    }
    /** Tests getWeight() correctly gets value **/
    void getWeightTest(TestCase* tc)
    {
        assert(tc->lvis->getWeight()==tc->weight);
    }
    /** Tests setWeight() correctly sets value **/
    void setWeightTest(TestCase* tc)
    {
        tc->lvis->setWeight(tc->weight = 3.0);
        getWeightTest(tc);
    }
    /** Tests getProperties() correctly gets value **/
    void getPropertiesTest(TestCase* tc)
    {
        unordered_map<string, string> props = tc->lvis->getProperties();
        assert(typeid(props)==typeid(unordered_map<string, string>));
        assert(props.at("color")== tc->color);
        assert(stod(props.at("thickness"))== tc->thick);
        assert(stod(props.at("opacity"))== tc->opac);
        assert(stod(props.at("weight"))== tc->weight);
    }
}
#undef UNIFORM_INITIALZATION
