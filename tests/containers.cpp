#include <fel/containers.hpp>
#include <gtest/gtest.h>

using namespace FEngine;

TEST(SeriesTest, TestGet) {
    vector<string> keys = {"a", "b"};
    vector<double> vals = {2., 1.};

    Series res(keys, vals);
    ASSERT_EQ(res["a"], 2.);
    ASSERT_EQ(res["b"], 1.);
}

TEST(SeriesTest, TestAt) {
    vector<string> keys = {"a", "b"};
    vector<double> vals = {2., 1.};

    Series res(keys, vals);
    ASSERT_EQ(res.at("a"), 2.);
    ASSERT_EQ(res.at("b"), 1.);   
}

TEST(SeriesTest, TestSize) {
    vector<string> keys = {"a", "b"};
    vector<double> vals = {2., 1.};

    Series res(keys, vals);
    ASSERT_EQ(res.size(), 2);   
}

TEST(SeriesTest, TestIteration) {
    vector<string> keys = {"a", "b", "c"};
    vector<double> vals = {2., 1., 3.};

    Series res(keys, vals);
    int counts = 0;
    for(Series::const_iterator it = res.begin(); it != res.end(); ++it) {
        ++counts;
        if(it->first == "a")
            ASSERT_EQ(it->second, 2.);
        else if (it->first == "b")
            ASSERT_EQ(it->second, 1.);
        else
            ASSERT_EQ(it->second, 3.);
        
    }
    ASSERT_EQ(counts, 3);
}

TEST(SeriesTest, TestPlus) {
    vector<string> keys1 = {"a", "b", "c"};
    vector<double> vals1 = {2., 1., 3.};
    Series lhs(keys1, vals1);

    vector<string> keys2 = {"b", "c", "d"};
    vector<double> vals2 = {2., 1., 3.};
    Series rhs(keys2, vals2);

    Series res = lhs + rhs;
    for(Series::const_iterator it = lhs.begin(); it != lhs.end(); ++it) {
        string key = it->first;
        double val1 = it->second;
        if(rhs.find(key) != rhs.end())
            ASSERT_EQ(res[key], val1 + rhs[key]);
        else
            ASSERT_EQ(res[key], val1);
    }

    for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
        string key = it->first;
        if(lhs.find(key) == lhs.end())
            ASSERT_EQ(res[key], it->second);
    }
}

TEST(SeriesTest, TestMinus) {
    vector<string> keys1 = {"a", "b", "c"};
    vector<double> vals1 = {2., 1., 3.};
    Series lhs(keys1, vals1);

    vector<string> keys2 = {"b", "c", "d"};
    vector<double> vals2 = {2., 1., 3.};
    Series rhs(keys2, vals2);

    Series res = lhs - rhs;
    for(Series::const_iterator it = lhs.begin(); it != lhs.end(); ++it) {
        string key = it->first;
        double val1 = it->second;
        if(rhs.find(key) != rhs.end())
            ASSERT_EQ(res[key], val1 - rhs[key]);
        else
            ASSERT_EQ(res[key], val1);
    }

    for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
        string key = it->first;
        if(lhs.find(key) == lhs.end())
            ASSERT_EQ(res[key], -it->second);
    }
}

TEST(SeriesTest, TestMultiply) {
    vector<string> keys1 = {"a", "b", "c"};
    vector<double> vals1 = {2., 1., 3.};
    Series lhs(keys1, vals1);

    vector<string> keys2 = {"b", "c", "d"};
    vector<double> vals2 = {2., 1., 3.};
    Series rhs(keys2, vals2);

    Series res = lhs * rhs;
    for(Series::const_iterator it = lhs.begin(); it != lhs.end(); ++it) {
        string key = it->first;
        double val1 = it->second;
        if(rhs.find(key) != rhs.end())
            ASSERT_EQ(res[key], val1 * rhs[key]);
        else
            ASSERT_EQ(res[key], val1);
    }

    for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
        string key = it->first;
        if(lhs.find(key) == lhs.end())
            ASSERT_EQ(res[key], it->second);
    }
}

TEST(SeriesTest, TestDivide) {
    vector<string> keys1 = {"a", "b", "c"};
    vector<double> vals1 = {2., 1., 3.};
    Series lhs(keys1, vals1);

    vector<string> keys2 = {"b", "c", "d"};
    vector<double> vals2 = {2., 1., 3.};
    Series rhs(keys2, vals2);

    Series res = lhs / rhs;
    for(Series::const_iterator it = lhs.begin(); it != lhs.end(); ++it) {
        string key = it->first;
        double val1 = it->second;
        if(rhs.find(key) != rhs.end())
            ASSERT_EQ(res[key], val1 / rhs[key]);
        else
            ASSERT_EQ(res[key], val1);
    }

    for(Series::const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
        string key = it->first;
        if(lhs.find(key) == lhs.end())
            ASSERT_EQ(res[key], 1. / it->second);
    }
}

TEST(SeriesTest, TestNegative) {
    vector<string> keys = {"a", "b"};
    vector<double> vals = {2., 1.};

    Series rhs(keys, vals);
    Series res = -rhs;
    ASSERT_EQ(res["a"], -2.);
    ASSERT_EQ(res["b"], -1.);
}

TEST(SeriesTest, TestRank) {
    vector<string> keys = {"a", "b", "c"};
    vector<double> vals = {4., 2., 6.};

    Series rhs(keys, vals);
    Series res = rank(rhs);
    ASSERT_EQ(res["a"], 1.);
    ASSERT_EQ(res["b"], 0.);
    ASSERT_EQ(res["c"], 2.);
}