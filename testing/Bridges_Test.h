#include <assert.h>
#include "Bridges.h"
using namespace bridges;

namespace Test_Bridges
{
    /** Contains obj for testing, as well as expected values of tests */
    struct TestCase
    {
        string key = "";
        string uname = "";
        unsigned int assign = 0;
        unsigned int size = 1;
        DataStructure* ds;
        bool visJSON = false;
    };

    /** TestCases pertaining to this object */
    vector<TestCase*> nativeCases()
    {
        vector<TestCase*> cases;
        cases.push_back(new TestCase());
        return cases;
    }

    void testGetProperties(TestCase* tc)
    {
        assert(Bridges::assignment()==tc->assign);
        assert(Bridges::userName()==tc->uname);
        assert(Bridges::apiKey()==tc->key);
        assert(Bridges::array_size()==tc->size);
        assert(Bridges::visualizeJSON()==tc->visJSON);
        assert(Bridges::ds_handle()==tc->ds);
    }
    void testSetProperties(TestCase* tc)
    {
        Bridges::assignment()=tc->assign = 9;
        Bridges::userName()=tc->uname = "user";
        Bridges::apiKey()=tc->key = "key";
        Bridges::array_size()=tc->size = 11;
        Bridges::visualizeJSON()=tc->visJSON = true;
        Bridges::ds_handle()=tc->ds = new Element<int>();
        testGetProperties(tc);

        Bridges::initialize(tc->key = "api",tc->uname = "name",tc->assign = 7);
        Bridges::setDataStructure(tc->ds = new GraphAdjList<int,int>()); tc->size = 1;
        testGetProperties(tc);

        Bridges::setDataStructure(tc->ds = new GraphAdjMatrix<int,int>(),tc->size = 21);
        testGetProperties(tc);
    }
    void testVisualize()
    {
        Bridges::visualizeJSON() = false;
        const string ERRMSG_NULL = "Error: visualizer called with a nullptr data structure",
                     ERRMSG_FULL = "Visualization has been performed maximum number of times for this assignment",
                     PASSMSG = "Success: Assignment posted to the server.";


        streambuf* original_cerr_Buf = cerr.rdbuf(); //Save cerr's normal buffer
        streambuf* original_cout_Buf = cout.rdbuf(); //Save cerr's normal buffer
        stringstream cerr_stream(""); //Stream for reading cerr
        stringstream cout_stream(""); //Stream for reading cout
        cout.rdbuf(cout_stream.rdbuf()); //Sets cout's new buffer
        cerr.rdbuf(cerr_stream.rdbuf()); //Set cerr's new buffer

        ///Expected to fail - nullptr
        Bridges::setDataStructure(nullptr);
        cerr_stream.str("");//Clear stream
        Bridges::visualize();
        //cout.rdbuf(originalBuf); //Returns cout's buffer to normal
        //cout<<endl<<endl<<endl/*<<stream.str()*/ << endl << stream.str().find(ERRMSG_NULL) <<endl;
        assert(cerr_stream.str().find(ERRMSG_NULL) != string::npos);

        Bridges::setDataStructure(new Element<int>());
        for(int i=0;i<99;i++) ///check overflow
        {
            ///Expected to pass
            cout_stream.str("");//Clear stream
            Bridges::visualize();
            assert(cout_stream.str().find(PASSMSG) != string::npos);
        }
        ///Expected to fail - overflow
        cout_stream.str("");//Clear stream
        Bridges::visualize();
        assert(cout_stream.str().find(ERRMSG_FULL) != string::npos);

        cout.rdbuf(original_cout_Buf); //Returns cout's buffer to normal
        cerr.rdbuf(original_cerr_Buf); //Returns cerr's buffer to normal
    }
    /** Runs Tests for any cases provided */
    void runTests(const vector<TestCase*>& cases)
    {
        for(TestCase* tc : cases)
        {
            testGetProperties(tc);
            testSetProperties(tc);
        }
        testVisualize();
    }
    /** Runs Tests for cases pertaining to this object */
    void runTests(){runTests(nativeCases());}
}
