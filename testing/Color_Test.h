#include <assert.h>
#include "Color.h"
using namespace bridges;

namespace Test_Color
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase
    {
        Color c;
        array<int,4> channels;
        TestCase(const Color& col) : c(col){}
    };
    /** TestCases pertaining to this object */
    vector<TestCase*> nativeCases()
    {
        vector<TestCase*> cases;

        cases.push_back(new TestCase(Color(0,0,0)));
        cases.back()->channels = array<int,4>{0,0,0,255};

        cases.push_back(new TestCase(Color(0,0,0,0)));
        cases.back()->channels = array<int,4>{0,0,0,0};

        cases.push_back(new TestCase(Color("black")));
        cases.back()->channels = array<int,4>{0,0,0,255};

        cases.push_back(new TestCase(Color("#000")));
        cases.back()->channels = array<int,4>{0,0,0,255};

        cases.push_back(new TestCase(Color("#0000")));
        cases.back()->channels = array<int,4>{0,0,0,0};

        cases.push_back(new TestCase(Color("#FF00FF")));
        cases.back()->channels = array<int,4>{255,0,255,255};

        cases.push_back(new TestCase(Color("#ff00ff00")));
        cases.back()->channels = array<int,4>{255,0,255,0};

        return cases;
    }

    void testOpacity(TestCase* tc)
    {
        assert(tc->c.isOpaque() == (tc->channels.at(3)==255));
        assert(tc->c.isTransparent() == (tc->channels.at(3)==0));
    }
    void testGetChannels(TestCase* tc)
    {
        assert(tc->c.getRed() == tc->channels.at(0));
        assert(tc->c.getGreen() == tc->channels.at(1));
        assert(tc->c.getBlue() == tc->channels.at(2));
        assert(tc->c.getAlpha() == tc->channels.at(3));
    }
    void testGetHex(TestCase* tc)
    {
        char red[3],blue[3],green[3],alpha[3];
        snprintf(red,3,"%x",tc->channels.at(0));
        snprintf(green,3,"%x",tc->channels.at(1));
        snprintf(blue,3,"%x",tc->channels.at(2));
        snprintf(alpha,3,"%x",tc->channels.at(3));
        assert(tc->c.getHexValue() == string("#")+(tc->channels.at(0)<16?"0":"")+red+(tc->channels.at(1)<16?"0":"")+green+(tc->channels.at(2)<16?"0":"")+blue+(tc->channels.at(3)<16?"0":"")+alpha);
    }
    void testSetChannels(TestCase* tc)
    {
        tc->c.setRed(tc->channels.at(0)=13);
        tc->c.setGreen(tc->channels.at(1)=37);
        tc->c.setBlue(tc->channels.at(2)=73);
        tc->c.setAlpha(tc->channels.at(3)=31);
        testGetChannels(tc);

        tc->c.setValue(tc->channels.at(0)=52,tc->channels.at(1)=83,tc->channels.at(2)=10); tc->channels.at(3)=255;
        testGetChannels(tc);
        tc->c.setValue(tc->channels.at(0)=128,tc->channels.at(1)=201,tc->channels.at(2)=71,tc->channels.at(3)=5);
        testGetChannels(tc);

        tc->c.setValue("#F0F"); tc->channels.at(0)=255;tc->channels.at(1)=0;tc->channels.at(2)=255;tc->channels.at(3)=255;
        testGetChannels(tc);
        tc->c.setValue("#F0F0"); tc->channels.at(0)=255;tc->channels.at(1)=0;tc->channels.at(2)=255;tc->channels.at(3)=0;
        testGetChannels(tc);
        tc->c.setValue("#00FF00"); tc->channels.at(0)=0;tc->channels.at(1)=255;tc->channels.at(2)=0;tc->channels.at(3)=255;
        testGetChannels(tc);
        tc->c.setValue("#FF00FF00"); tc->channels.at(0)=255;tc->channels.at(1)=0;tc->channels.at(2)=255;tc->channels.at(3)=0;
        testGetChannels(tc);
    }
    void testEquality()
    {
        assert(Color("white") == Color("#FFFFFFFF"));
        assert(Color("#FFFFFF") == Color("wHiTe"));

        assert(Color("Black") == Color("#000F"));
        assert(Color("#000") == Color("bLACK"));

        assert(Color("RED") != Color("#F000"));
        assert(Color("#FF000000") != Color("red"));
    }

    /** Runs Tests for any cases provided */
    void runTests(const vector<TestCase*>& cases)
    {
        for(TestCase* tc : cases)
        {
            testOpacity(tc);
            testGetChannels(tc);
            testSetChannels(tc);
            testGetHex(tc);
        }
        testEquality();
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}
