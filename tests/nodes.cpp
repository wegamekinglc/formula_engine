#include <fel/nodes.hpp>
#include <fel/settings.hpp>
#include <gtest/gtest.h>

using namespace FEngine;

TEST(TestNodes, TestLast) {
    DataPack data;
    data["aapl"] = map<string, map<DateTime, double>>();
    data["ibm"] = map<string, map<DateTime, double>>();
    data["aapl"]["close"] = map<DateTime, double>();
    data["ibm"]["close"] = map<DateTime, double>();
    data["aapl"]["close"]["2018-01-05"] = 2.;
    data["ibm"]["close"]["2018-01-05"] = 3.;

    GlobalSymbols symbols({"aapl", "ibm"});
    Last close("close");
    Series res = close.calculate(data, "2018-01-05");

    ASSERT_EQ(res["aapl"], 2.);
    ASSERT_EQ(res["ibm"], 3.);
}

TEST(TestNodes, TestPlusOperator) {
    DataPack data;
    data["aapl"] = map<string, map<DateTime, double>>();
    data["ibm"] = map<string, map<DateTime, double>>();
    data["aapl"]["close"] = map<DateTime, double>();
    data["ibm"]["close"] = map<DateTime, double>();
    data["aapl"]["close"]["2018-01-05"] = 2.;
    data["ibm"]["close"]["2018-01-05"] = 3.;

    GlobalSymbols symbols({"aapl", "ibm"});
    Last close1("close");
    Last close2("close");

    PlusOperator combined = close1 + close2;
    Series res = combined.calculate(data, "2018-01-05");

    ASSERT_EQ(res["aapl"], 4.);
    ASSERT_EQ(res["ibm"], 6.);
}

TEST(TestNodes, TestMinusOperator) {
    DataPack data;
    data["aapl"] = map<string, map<DateTime, double>>();
    data["ibm"] = map<string, map<DateTime, double>>();
    data["aapl"]["close"] = map<DateTime, double>();
    data["ibm"]["close"] = map<DateTime, double>();
    data["aapl"]["close"]["2018-01-05"] = 2.;
    data["ibm"]["close"]["2018-01-05"] = 3.;

    GlobalSymbols symbols({"aapl", "ibm"});
    Last close1("close");
    Last close2("close");

    MinusOperator combined = close1 - close2;
    Series res = combined.calculate(data, "2018-01-05");

    ASSERT_EQ(res["aapl"], 0.);
    ASSERT_EQ(res["ibm"], 0.);
}

TEST(TestNodes, TestMultiplyOperator) {
    DataPack data;
    data["aapl"] = map<string, map<DateTime, double>>();
    data["ibm"] = map<string, map<DateTime, double>>();
    data["aapl"]["close"] = map<DateTime, double>();
    data["ibm"]["close"] = map<DateTime, double>();
    data["aapl"]["close"]["2018-01-05"] = 2.;
    data["ibm"]["close"]["2018-01-05"] = 3.;

    GlobalSymbols symbols({"aapl", "ibm"});
    Last close1("close");
    Last close2("close");

    MultiplyOperator combined = close1 * close2;
    Series res = combined.calculate(data, "2018-01-05");

    ASSERT_EQ(res["aapl"], 4.);
    ASSERT_EQ(res["ibm"], 9.);
}

TEST(TestNodes, TestDivideOperator) {
    DataPack data;
    data["aapl"] = map<string, map<DateTime, double>>();
    data["ibm"] = map<string, map<DateTime, double>>();
    data["aapl"]["close"] = map<DateTime, double>();
    data["ibm"]["close"] = map<DateTime, double>();
    data["aapl"]["close"]["2018-01-05"] = 2.;
    data["ibm"]["close"]["2018-01-05"] = 3.;

    GlobalSymbols symbols({"aapl", "ibm"});
    Last close1("close");
    Last close2("close");

    DivideOperator combined = close1 / close2;
    Series res = combined.calculate(data, "2018-01-05");

    ASSERT_EQ(res["aapl"], 1.);
    ASSERT_EQ(res["ibm"], 1.);
}