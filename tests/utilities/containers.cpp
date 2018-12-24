#include <fel/utilities/containers.hpp>
#include <gtest/gtest.h>

using namespace FEngine;

TEST(SeriesTest, TestGet) {
    Vector_<String_> keys = {"a", "b"};
    Vector_<double> vals = {2., 1.};

    Series res(keys, vals);
    ASSERT_EQ(res["a"], 2.);
    ASSERT_EQ(res["b"], 1.);
}

TEST(SeriesTest, TestAt) {
    Vector_<String_> keys = {"a", "b"};
    Vector_<double> vals = {2., 1.};

    Series res(keys, vals);
    ASSERT_EQ(res.at("a"), 2.);
    ASSERT_EQ(res.at("b"), 1.);   
}

TEST(SeriesTest, TestSize) {
    Vector_<String_> keys = {"a", "b"};
    Vector_<double> vals = {2., 1.};

    Series res(keys, vals);
    ASSERT_EQ(res.size(), 2);   
}

TEST(SeriesTest, TestIteration) {
    Vector_<String_> keys = {"a", "b", "c"};
    Vector_<double> vals = {2., 1., 3.};

    Series res(keys, vals);
    int counts = 0;
    for(auto &pair: res) {
        ++counts;
        if(pair.first == "a")
            ASSERT_EQ(pair.second, 2.);
        else if (pair.first == "b")
            ASSERT_EQ(pair.second, 1.);
        else
            ASSERT_EQ(pair.second, 3.);
        
    }
    ASSERT_EQ(counts, 3);
}

TEST(SeriesTest, TestPlus) {
    Vector_<String_> keys1 = {"a", "b", "c"};
    Vector_<double> vals1 = {2., 1., 3.};
    Series lhs(keys1, vals1);

    Vector_<String_> keys2 = {"b", "c", "d"};
    Vector_<double> vals2 = {2., 1., 3.};
    Series rhs(keys2, vals2);

    Series res = lhs + rhs;
    for(auto &pair: lhs) {
        String_ key = pair.first;
        double val1 = pair.second;
        if(rhs.find(key) != rhs.end())
            ASSERT_EQ(res[key], val1 + rhs[key]);
        else
            ASSERT_EQ(res[key], val1);
    }

    for(auto &pair: rhs) {
        String_ key = pair.first;
        if(lhs.find(key) == lhs.end())
            ASSERT_EQ(res[key], pair.second);
    }
}

TEST(SeriesTest, TestMinus) {
    Vector_<String_> keys1 = {"a", "b", "c"};
    Vector_<double> vals1 = {2., 1., 3.};
    Series lhs(keys1, vals1);

    Vector_<String_> keys2 = {"b", "c", "d"};
    Vector_<double> vals2 = {2., 1., 3.};
    Series rhs(keys2, vals2);

    Series res = lhs - rhs;
    for(auto &pair: lhs) {
        String_ key = pair.first;
        double val1 = pair.second;
        if(rhs.find(key) != rhs.end())
            ASSERT_EQ(res[key], val1 - rhs[key]);
        else
            ASSERT_EQ(res[key], val1);
    }

    for(auto &pair: rhs) {
        String_ key = pair.first;
        if(lhs.find(key) == lhs.end())
            ASSERT_EQ(res[key], -pair.second);
    }
}

TEST(SeriesTest, TestMultiply) {
    Vector_<String_> keys1 = {"a", "b", "c"};
    Vector_<double> vals1 = {2., 1., 3.};
    Series lhs(keys1, vals1);

    Vector_<String_> keys2 = {"b", "c", "d"};
    Vector_<double> vals2 = {2., 1., 3.};
    Series rhs(keys2, vals2);

    Series res = lhs * rhs;
    for(auto &pair: lhs) {
        String_ key = pair.first;
        double val1 = pair.second;
        if(rhs.find(key) != rhs.end())
            ASSERT_EQ(res[key], val1 * rhs[key]);
        else
            ASSERT_EQ(res[key], val1);
    }

    for(auto it = rhs.begin(); it != rhs.end(); ++it) {
        String_ key = it->first;
        if(lhs.find(key) == lhs.end())
            ASSERT_EQ(res[key], it->second);
    }
}

TEST(SeriesTest, TestDivide) {
    Vector_<String_> keys1 = {"a", "b", "c"};
    Vector_<double> vals1 = {2., 1., 3.};
    Series lhs(keys1, vals1);

    Vector_<String_> keys2 = {"b", "c", "d"};
    Vector_<double> vals2 = {2., 1., 3.};
    Series rhs(keys2, vals2);

    Series res = lhs / rhs;
    for(auto &pair: lhs) {
        String_ key = pair.first;
        double val1 = pair.second;
        if(rhs.find(key) != rhs.end())
            ASSERT_EQ(res[key], val1 / rhs[key]);
        else
            ASSERT_EQ(res[key], val1);
    }

    for(auto it = rhs.begin(); it != rhs.end(); ++it) {
        String_ key = it->first;
        if(lhs.find(key) == lhs.end())
            ASSERT_EQ(res[key], 1. / it->second);
    }
}

TEST(SeriesTest, TestNegative) {
    Vector_<String_> keys = {"a", "b"};
    Vector_<double> vals = {2., 1.};

    Series rhs(keys, vals);
    Series res = -rhs;
    ASSERT_EQ(res["a"], -2.);
    ASSERT_EQ(res["b"], -1.);
}

TEST(SeriesTest, TestRank) {
    Vector_<String_> keys = {"a", "b", "c"};
    Vector_<double> vals = {4., 2., 6.};

    Series rhs(keys, vals);
    Series res = rank(rhs);
    ASSERT_EQ(res["a"], 1.);
    ASSERT_EQ(res["b"], 0.);
    ASSERT_EQ(res["c"], 2.);
}