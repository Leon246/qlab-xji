#define BOOST_TEST_MODULE Quantlabcodingtest unittest
#include <boost/test/included/unit_test.hpp>
#include "Quantlabcodingtest.h"

BOOST_AUTO_TEST_CASE(asset_test)
{
    BOOST_TEST_MESSAGE("Testing asset class");
    BOOST_TEST_MESSAGE("Create asset object with Symbol: aaa, TimeStamp: 52924702, Quantity: 13, Price: 1136");
    asset a1("aaa", 52924702, 13, 1136);
    BOOST_CHECK_EQUAL(a1.get_name(), "aaa");
    BOOST_CHECK_EQUAL(a1.get_max_gap(), 0);
    BOOST_CHECK_EQUAL(a1.get_tot_vol(), 13);
    BOOST_CHECK_EQUAL(a1.get_max_price(), 1136);
    BOOST_CHECK_EQUAL(a1.get_wa_price(), 1136);

    BOOST_TEST_MESSAGE("Update existing class asset object with TimeStamp: 52930489, Quantity: 18, Price: 1222");
    a1.update(52930489,18,1222);
    BOOST_CHECK_EQUAL(a1.get_max_gap(), 5787);
    BOOST_CHECK_EQUAL(a1.get_tot_vol(), 31);
    BOOST_CHECK_EQUAL(a1.get_max_price(), 1222);
    BOOST_CHECK_EQUAL(a1.get_wa_price(), 1185);

    BOOST_TEST_MESSAGE("Update existing class asset object with TimeStamp: 52931654, Quantity: 9, Price: 1077");
    a1.update(52931654,9,1077);
    BOOST_CHECK_EQUAL(a1.get_max_gap(), 5787);
    BOOST_CHECK_EQUAL(a1.get_tot_vol(), 40);
    BOOST_CHECK_EQUAL(a1.get_max_price(), 1222);
    BOOST_CHECK_EQUAL(a1.get_wa_price(), 1161);

    BOOST_TEST_MESSAGE("Testing << overloading");
    std::ostringstream os1;
    os1 << a1;
    string s1 = os1.str();
    string s2 = "aaa,5787,40,1161,1222\n";    
    BOOST_CHECK_EQUAL(s1, s2);
}

BOOST_AUTO_TEST_CASE(query_readline_test)
{
    BOOST_TEST_MESSAGE("Testing query readline function");
    query q1;
    BOOST_TEST_MESSAGE("Read line with Symbol: aaa, TimeStamp: 52924702, Quantity: 13, Price: 1136");
    q1.readline("aaa", 52924702, 13, 1136);
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aaa").get_name(), "aaa");
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aaa").get_max_gap(), 0);
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aaa").get_tot_vol(), 13);
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aaa").get_max_price(), 1136);
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aaa").get_wa_price(), 1136);

    BOOST_TEST_MESSAGE("Read line with Symbol: aac, TimeStamp: 52924702, Quantity: 20, Price: 477");
    q1.readline("aac", 52924702, 20, 477);
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aac").get_name(), "aac");
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aac").get_max_gap(), 0);
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aac").get_tot_vol(), 20);
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aac").get_max_price(), 477);
    BOOST_CHECK_EQUAL(q1.get_asset_db().at("aac").get_wa_price(), 477);
}

BOOST_AUTO_TEST_CASE(query_process_and_output_test)
{
    BOOST_TEST_MESSAGE("Creating input file for query process testing");
    std::ofstream inputtest("inputtest.csv");
    inputtest << "52924702,aaa,13,1136" << std::endl;
    inputtest << "52924702,aac,20,477" << std::endl;
    inputtest << "52925641,aab,31,907" << std::endl;
    inputtest << "52927350,aab,29,724" << std::endl;
    inputtest << "52927783,aac,21,638" << std::endl;
    inputtest << "52930489,aaa,18,1222" << std::endl;
    inputtest << "52931654,aaa,9,1077" << std::endl;
    inputtest << "52933453,aab,9,756" << std::endl;
    inputtest.close();

    BOOST_TEST_MESSAGE("Testing query file process function");
    query q2;
    q2.process("inputtest.csv");
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aaa").get_name(), "aaa");
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aaa").get_max_gap(), 5787);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aaa").get_tot_vol(), 40);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aaa").get_wa_price(), 1161);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aaa").get_max_price(), 1222);

    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aab").get_name(), "aab");
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aab").get_max_gap(), 6103);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aab").get_tot_vol(), 69);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aab").get_wa_price(), 810);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aab").get_max_price(), 907);

    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aac").get_name(), "aac");
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aac").get_max_gap(), 3081);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aac").get_tot_vol(), 41);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aac").get_wa_price(), 559);
    BOOST_CHECK_EQUAL(q2.get_asset_db().at("aac").get_max_price(), 638);

    BOOST_TEST_MESSAGE("Testing sorted output");
    std::ostringstream os2;
    os2 << q2;
    string s1 = os2.str();
    string s2 = "aaa,5787,40,1161,1222\naab,6103,69,810,907\naac,3081,41,559,638\n";    
    BOOST_CHECK_EQUAL(s1, s2);
}