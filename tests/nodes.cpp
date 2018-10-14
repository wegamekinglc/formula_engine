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