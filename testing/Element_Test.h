#include <string>
#include <assert.h>
using namespace std;
#include "Element.h"
using namespace bridges;

/** Preprocessor macros for readablity and ease of change **/
#ifndef TYPE
    #define TYPE string ///Template type parameter
#endif //TYPE
#define UNIFORM_INITIALZATION(...) (new TestCase(new Element<TYPE>(__VA_ARGS__))) ///Syntactic Sugar

/** Namespace used to prevent naming interference with other files **/
namespace ElementTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        Element<TYPE>*const ele;
        string label = "";
        TYPE value = TYPE();
        ///Constructor - initializes constant
        TestCase(Element<TYPE>* e) : ele(e){}
        ///Assignment Operator
        TestCase& operator=(const TestCase& that)
        {
            label = that.label;
            value = that.value;
            return *this;
        }
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = UNIFORM_INITIALZATION();
        cases.push_back(tc1);

        TestCase* tc2 = UNIFORM_INITIALZATION("A");
        tc2->value = "A";
        cases.push_back(tc2);

        TestCase* tc3 = UNIFORM_INITIALZATION("B","C");
        tc3->label = "B";
        tc3->value = "C";
        cases.push_back(tc3);

        TestCase* tc4 = UNIFORM_INITIALZATION(*(tc2->ele));
        tc4->label = tc2->label;
        tc4->value = tc2->value;
        cases.push_back(tc4);

        Element<string>* e1 = new Element<string>("D","E");
        *e1 = *(tc3->ele); ///Equals operator testcase
        TestCase* tc5 = new TestCase(e1);
        *tc5 = *tc3;
        cases.push_back(tc5);

        Element<string>* e2 = new Element<string>("F","G");
        *e2 = *e2; ///Equals operator to self testcase
        TestCase* tc6 = new TestCase(e2);
        tc6->label = "F";
        tc6->value = "G";
        cases.push_back(tc6);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getIdentifierTest(const vector<TestCase*>&,TestCase*);
    void getLabelTest(TestCase*);
    void getValueTest(TestCase*);
    void getVisualizerTest(TestCase*);
    void getLinkVisualizerTest(TestCase*);
    void getRepresentationTest(TestCase*);
    void setLabelTest(TestCase*);
    void setValueTest(TestCase*);
    void setVisualizerTest(TestCase*);

    /** Runs Tests for all native Element Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all give Element Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            getIdentifierTest(cases,tc);
            getLabelTest(tc);
            //getLinkVisualizerTest(tc);
            //getRepresentationTest(tc);
            //getValueTest(tc);
            getVisualizerTest(tc);
            setLabelTest(tc);
            setValueTest(tc);
            //setVisualizerTest(tc);
            ///Deconstructor's deep delete property is untestable
        }
    }
    /** Tests getIdentifier() returns unique values for different objects */
    void getIdentifierTest(const vector<TestCase*>& cases, TestCase* tc)
    {
        for(auto* tc2: cases)
        {
            if(tc->ele!=tc2->ele)
            {
                assert(tc->ele->getIdentifier()!=tc2->ele->getIdentifier());
            }
        }
    }
    /** Tests getLabel() correctly gets value */
    void getLabelTest(TestCase* tc)
    {
        assert(tc->ele->getLabel()==tc->label);
    }
    /** Tests getValue() correctly gets value */
    void getValueTest(TestCase* tc)
    {
        assert(tc->ele->getValue()==tc->value);
    }
    /** Tests getVisualizer() returns a non-null ElementVisualizer */
    void getVisualizerTest(TestCase* tc)
    {
        auto* elvis = tc->ele->getVisualizer();
        assert(elvis!=nullptr);
    }
    /** Tests getLinkVisualizer() returns a non-null LinkVisualizer */
    void getLinkVisualizerTest(TestCase* tc)
    {
        ///Tests LinkVisualizer to self
        auto* lvis = tc->ele->getLinkVisualizer(tc->ele);
        assert(lvis!=nullptr);
    }
    /** Tests getRepresentation() gets JSON **/
    void getRepresentationTest(TestCase* tc)
    {

    }
    /** Tests setLabel() correctly sets value **/
    void setLabelTest(TestCase* tc)
    {
        tc->ele->setLabel(tc->label = "X");
        getLabelTest(tc);
    }
    /** Tests setValue() correctly sets value **/
    void setValueTest(TestCase* tc)
    {
        tc->ele->setValue(tc->value = "Y");
        getValueTest(tc);
    }
    /** Tests setVisualizer() correctly sets value **/
    void setVisualizerTest(TestCase* tc)
    {
        /*
        ElementVisualizer* elvis = new ElementVisualizer();
        tc->ele->setVisualizer(elvis);
        assert(tc->ele->getVisualizer()==elvis);
        */
    }
}
#undef UNIFORM_INITIALZATION
#undef TYPE

