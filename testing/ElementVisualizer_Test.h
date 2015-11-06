#include <string>
#include <assert.h>
using namespace std;
#include "ElementVisualizer.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#define UNIFORM_INITIALZATION(...) (new TestCase(new ElementVisualizer(__VA_ARGS__))) ///Syntactic Sugar

/** Namespace used to prevent naming interference with other files **/
namespace ElementVisualizerTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        ElementVisualizer*const elvis;
        string key = "";
        double size = 10.0;
        string color = "green";
        string shape = "circle";
        double opac = 1.0;
        ///Constructor - initializes constant
        TestCase(ElementVisualizer* e) : elvis(e){}
        ///Assignment Operator
        TestCase& operator=(const TestCase& that)
        {
            key = that.key;
            size = that.size;
            color = that.color;
            shape = that.shape;
            opac = that.opac;
            return *this;
        }
    };
    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = UNIFORM_INITIALZATION();
        cases.push_back(tc1);

        TestCase* tc2 = UNIFORM_INITIALZATION("blue");
        tc2->color = "blue";
        cases.push_back(tc2);

        TestCase* tc3 = UNIFORM_INITIALZATION("yellow","square");
        tc3->color = "yellow";
        tc3->shape = "square";
        cases.push_back(tc3);

        TestCase* tc4 = UNIFORM_INITIALZATION(20.0);
        tc4->size = 20.0;
        cases.push_back(tc4);

        TestCase* tc5 = UNIFORM_INITIALZATION("red","cross",0.5,5.0);
        tc5->color = "red";
        tc5->shape = "cross";
        tc5->opac = 0.5;
        tc5->size = 5.0;
        cases.push_back(tc5);

        TestCase* tc6 = UNIFORM_INITIALZATION(*(tc5->elvis));
        *tc6 = *tc5;
        cases.push_back(tc6);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getSizeTest(TestCase*);
    void setSizeTest(TestCase*);
    void getColorTest(TestCase*);
    void setColorTest(TestCase*);
    void getShapeTest(TestCase*);
    void setShapeTest(TestCase*);
    void getOpacityTest(TestCase*);
    void setOpacityTest(TestCase*);
    void setKeyTest(TestCase*);
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
            getSizeTest(tc);
            setSizeTest(tc);
            getColorTest(tc);
            setColorTest(tc);
            getShapeTest(tc);
            setShapeTest(tc);
            getOpacityTest(tc);
            setOpacityTest(tc);
            getPropertiesTest(tc);
            setKeyTest(tc); ///After properties test
        }
    }
    /** Tests getSize() correctly gets value **/
    void getSizeTest(TestCase* tc)
    {
        assert(tc->elvis->getSize()==tc->size);
    }
    /** Tests setSize() correctly sets value **/
    void setSizeTest(TestCase* tc)
    {
        tc->elvis->setSize(tc->size = 15.0);
        getSizeTest(tc);
    }
    /** Tests getColor() correctly gets value **/
    void getColorTest(TestCase* tc)
    {
        assert(tc->elvis->getColor()==tc->color);
    }
    /** Tests setColor() correctly sets value **/
    void setColorTest(TestCase* tc)
    {
        tc->elvis->setColor(tc->color = "pink"); //only lower case
        getColorTest(tc);

        tc->elvis->setColor(tc->color = "BlAcK"); //contains upper case
        getColorTest(tc);
    }
    /** Tests getShape() correctly gets value **/
    void getShapeTest(TestCase* tc)
    {
        assert(tc->elvis->getShape()==tc->shape);
    }
    /** Tests setShape() correctly sets value **/
    void setShapeTest(TestCase* tc)
    {
        tc->elvis->setShape(tc->shape = "diamond"); //only lower case
        getShapeTest(tc);

        tc->elvis->setShape(tc->shape = "cRoSs"); //contains upper case
        getShapeTest(tc);
    }
    /** Tests getOpacity() correctly gets value **/
    void getOpacityTest(TestCase* tc)
    {
        assert(tc->elvis->getOpacity()==tc->opac);
    }
    /** Tests setOpacity() correctly sets value **/
    void setOpacityTest(TestCase* tc)
    {
        tc->elvis->setOpacity(tc->opac = 0.2);
        getOpacityTest(tc);
    }
    /** Tests getProperties() correctly gets value **/
    void getPropertiesTest(TestCase* tc)
    {
        unordered_map<string, string> props = tc->elvis->getProperties();
        assert(typeid(props)==typeid(unordered_map<string, string>));
        assert(props.at("color")== tc->color);
        assert(props.at("shape")== tc->shape);
        assert(stod(props.at("opacity"))== tc->opac);
        assert(stod(props.at("size"))== tc->size);
    }
    /** Tests setKey() correctly sets value **/
    void setKeyTest(TestCase* tc)
    {
        tc->elvis->setKey(tc->key = "k");
        assert(tc->elvis->getProperties().at("key")== tc->key);
    }
}
#undef UNIFORM_INITIALZATION
