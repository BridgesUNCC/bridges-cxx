#include <string>
#include <assert.h>
using namespace std;
#include "Element.h"
using namespace bridges;

/** Namespace used to prevent naming interference with other files **/
namespace ValidationTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        Validation*const valid;
        ///Constructor - initializes const
        TestCase(Validation* e) : valid(e){}
    };

    vector<TestCase*> testCases;
    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = new TestCase(new Validation());
        cases.push_back(tc1);

        return cases;
    }
    void runTests();
    void runTests(const vector<TestCase*>&);
    void getCurrentTest(const vector<TestCase*>&);
    void validateColorTest(TestCase*);
    void validateShapeTest(TestCase*);
    void validateOpacityTest(TestCase*);
    void validateSizeTest(TestCase*);
    void validateThicknessTest(TestCase*);
    void validateWeightTest(TestCase*);
    void validate_ADT_size_Test(TestCase*);

    /** Runs Tests for all native Validation Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all given Validation Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        getCurrentTest(cases); ///Static test, should come before non-static tests
        for(auto* tc: testCases)
        {
            validateColorTest(tc);
            validateShapeTest(tc);
            validateOpacityTest(tc);
            validateSizeTest(tc);
            validateThicknessTest(tc);
            validateWeightTest(tc);
            validate_ADT_size_Test(tc);
        }
    }
    /** Tests getCurrent() returns the most recently created Validation */
    void getCurrentTest(const vector<TestCase*>& cases)
    {
        assert(Validation::getCurrent() == cases.back()->valid);
    }
    /** Tests validateColor() correctly validates against list */
    void validateColorTest(TestCase* tc)
    {
        string color="";
        ///Tests supposed to pass
        try
        {
            tc->valid->validateColor(color="blue"); //string rep
            tc->valid->validateColor(color="#a0f"); //#RGB
            tc->valid->validateColor(color="#af01f3"); //#RRGGBB
        }
        catch(...)
        {
            perror(("Valid color: "+color+" threw error").c_str());
            abort();
        }

        ///Tests supposed to fail
        try{tc->valid->validateColor(color="bloo");}//string rep
        catch(...)
        {
            try{tc->valid->validateColor(color="#ggg");}//#RGB
            catch(...)
            {
                try{tc->valid->validateColor(color="#gfad9r");}//#RRGGBB
                catch(...){return;}//Invalid input failed correctly
            }
        }

        perror(("Invalid color: "+color+" didn't throw error").c_str());
        abort();
    }
    /** Tests validateShape() correctly validates against list */
    void validateShapeTest(TestCase* tc)
    {
        string shape="";
        ///Tests supposed to pass
        try{tc->valid->validateShape(shape="circle");}
        catch(...)
        {
            perror(("Valid shape: "+shape+" threw error").c_str());
            abort();
        }

        ///Tests supposed to fail
        try{tc->valid->validateShape(shape="pentagon");}
        catch(...){return;}//Invalid input failed correctly

        perror(("Invalid shape: "+shape+" didn't throw error").c_str());
        abort();
    }
    /** Tests validateOpacity() correctly validates bounds - [0,1] */
    void validateOpacityTest(TestCase* tc)
    {
        double opacity;
        ///Tests supposed to pass
        try
        {
            tc->valid->validateOpacity(opacity=0.0); //Lower Bound
            tc->valid->validateOpacity(opacity=0.1337); //Included Value
            tc->valid->validateOpacity(opacity=1.0); //Upper Bound
        }
        catch(...)
        {
            perror(("Valid opacity: "+to_string(opacity)+" threw error").c_str());
            abort();
        }

        ///Tests supposed to fail
        try{tc->valid->validateOpacity(opacity=-0.1);}//Past Lower Bound
        catch(...)
        {
            try{tc->valid->validateOpacity(opacity=1.1);}//Past Upper Bound
            catch(...){return;}//Invalid input failed correctly
        }
        perror(("Invalid opacity: "+to_string(opacity)+" didn't throw error").c_str());
        abort();
    }
    /** Tests validateSize() correctly validates bounds - [0,50] */
    void validateSizeTest(TestCase* tc)
    {
        double size;
        ///Tests supposed to pass
        try
        {
            tc->valid->validateSize(size=0.0);//Lower Bound
            tc->valid->validateSize(size=13.37);//Included Value
            tc->valid->validateSize(size=50.0);//Upper Bound
        }
        catch(...)
        {
            perror(("Valid size: "+to_string(size)+" threw error").c_str());
            abort();
        }

        ///Tests supposed to fail
        try{tc->valid->validateSize(size=-0.1);} //Past Lower Bound
        catch(...)
        {
            try{tc->valid->validateSize(size=50.1);} //Past Upper Bound
            catch(...){return;}//Invalid input failed correctly
        }
        perror(("Invalid size: "+to_string(size)+" didn't throw error").c_str());
        abort();
    }
    /** Tests validateThickness() correctly validates bounds - [0,10] */
    void validateThicknessTest(TestCase* tc)
    {
        double thickness;
        ///Tests supposed to pass
        try
        {
            tc->valid->validateThickness(thickness=0.0); //Lower Bound
            tc->valid->validateThickness(thickness=1.337); //Included Value
            tc->valid->validateThickness(thickness=10.0); //Upper Bound
        }
        catch(...)
        {
            perror(("Valid thickness: "+to_string(thickness)+" threw error").c_str());
            abort();
        }

        ///Tests supposed to fail
        try{tc->valid->validateThickness(thickness=-0.1);}//Past Lower Bound
        catch(...)
        {
            try{tc->valid->validateThickness(thickness=10.1);}//Past Upper Bound
            catch(...){return;}//Invalid input failed correctly
        }
        perror(("Invalid thickness: "+to_string(thickness)+" didn't throw error").c_str());
        abort();
    }
    /** Tests validateWeight() correctly validates bounds - [0,inf) */
    void validateWeightTest(TestCase* tc)
    {
        double weight;
        ///Tests supposed to pass
        try
        {
            tc->valid->validateWeight(weight=0.0);//Lower Bound
            tc->valid->validateWeight(weight=13.37);//Included Value
        }
        catch(...)
        {
            perror(("Valid weight: "+to_string(weight)+" threw error").c_str());
            abort();
        }
        ///Tests supposed to fail
        try{tc->valid->validateWeight(weight=-1.0);}//Past Lower Bound
        catch(...){return;}//Invalid input failed correctly
        perror(("Invalid weight: "+to_string(weight)+" didn't throw error").c_str());
        abort();
    }
    /** Tests validate_ADT_size() correctly validates bounds - [0,5000) */
    void validate_ADT_size_Test(TestCase* tc)
    {
        int adtSize;
        ///Tests supposed to pass
        try
        {
            tc->valid->validate_ADT_size(adtSize=0); //Lower Bound
            tc->valid->validate_ADT_size(adtSize=1337); //Included Value
            tc->valid->validate_ADT_size(adtSize=4999); //Upper Bound
        }
        catch(...)
        {
            perror(("Valid adtSize: "+to_string(adtSize)+" threw error").c_str());
            abort();
        }
        ///Tests supposed to fail
        try{tc->valid->validate_ADT_size(adtSize=-1);}//Past Lower Bound
        catch(...)
        {
            try{tc->valid->validate_ADT_size(adtSize=5000);}//Past Upper Bound
            catch(...){return;}//Invalid input failed correctly
        }
        perror(("Invalid adtSize: "+to_string(adtSize)+" didn't throw error").c_str());
        abort();
    }
}
