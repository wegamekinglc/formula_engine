#include<fel/types.hpp>
#include<gtest/gtest.h>

using namespace FEngine;

TEST(TypeTest, TestDependsMerge) {
    Depends d1 = Depends();
    Depends d2 = Depends();
    d1["a"] = {"2018-01-01"};
    d1["b"] = {"2018-03-01"};
    d2["c"] = {"2018-05-01"};

    Depends res = mergeDepends(d1, d2);
    ASSERT_EQ(res["a"], d1["a"]);
    ASSERT_EQ(res["b"], d1["b"]);
    ASSERT_EQ(res["c"], d2["c"]);
}