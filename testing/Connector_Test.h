#include <string>
#include <assert.h>
using namespace std;
#include "Connector.h"
using namespace bridges;

/** Namespace used to prevent naming interference with other files **/
namespace ConnectorTester
{
    /** POD struct to hold element for testing and expected values **/
    struct TestCase
    {
        ///Initializes to default value
        Connector*const conn;
        string surl = "http://127.0.0.1:3000";
        ///Constructor - initializes constant
        TestCase(Connector* e) : conn(e){}
    };

    /** Returns list of hard coded TestCases **/
    vector<TestCase*> nativeTestCases()
    {
        vector<TestCase*> cases;

        TestCase* tc1 = new TestCase(new Connector());
        cases.push_back(tc1);

        return cases;
    }

    void runTests();
    void runTests(const vector<TestCase*>&);
    void getServerURLTest(TestCase*);
    void setServerURLTest(TestCase*);
    void postTest(TestCase*);

    /** Runs Tests for all native Connector Testcases **/
    void runTests()
    {
        runTests(nativeTestCases());
    }
    /** Runs Tests for all given Connector Testcases **/
    void runTests(const vector<TestCase*>& cases)
    {
        for(auto* tc: cases)
        {
            getServerURLTest(tc);
            setServerURLTest(tc);
            postTest(tc);
        }
    }
    /** Tests getServerURL correctly gets value **/
    void getServerURLTest(TestCase* tc)
    {
        assert(tc->conn->getServerURL()==tc->surl);
    }
    /** Tests gsetServerURL correctly sets value **/
    void setServerURLTest(TestCase* tc)
    {
        tc->conn->setServerURL(tc->surl = "url.goes.here");
        getServerURLTest(tc);
    }
    /** Tests post() correctly posts **/
    void postTest(TestCase* tc)
    {
        const string PASS_MSG = "Success. Assignment Posted to the server..\n"; //Messgae printed when successful
        const string VALID_URL = "http://bridges-cs.herokuapp.com/assignments/1.00/?apikey=671470050308";
        auto vis = ADTVisualizer<int,string>(); vis.setArraySize(0);
        const string JSON_ELEMENT = vis.getDataStructureRepresentation(new Element<string>("A","B"));

        streambuf* originalBuf = cout.rdbuf(); //Save cout's normal buffer
        stringstream stream(""); //Stream for reading
        cout.rdbuf(stream.rdbuf()); //Set cout's new buffer

        ///Expected to fail - trash url and trash json
        stream.str("");//Clear stream
        tc->conn->post("url","json");
        assert(stream.str() != PASS_MSG);

        ///Expected to pass - trash json
        stream.str("");//Clear stream
        tc->conn->post(VALID_URL,"json");
        assert(stream.str() == PASS_MSG);

        ///Expected to pass - trash json, but correct format
        stream.str("");//Clear stream
        tc->conn->post(VALID_URL,"{\"name\":\"test\"}");
        assert(stream.str() == PASS_MSG);

        ///Expected to pass
        stream.str("");//Clear stream
        tc->conn->post(VALID_URL,JSON_ELEMENT);
        assert(stream.str() == PASS_MSG);

        cout.rdbuf(originalBuf); //Returns cout's buffer to normal
    }
}
