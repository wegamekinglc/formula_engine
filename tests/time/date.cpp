#include <fel/time/date.hpp>
#include <gtest/gtest.h>

using namespace FEngine;

TEST(DateTest, TestDateNull) {
    Date date;
    ASSERT_EQ(date.serial(), 0);
}

TEST(DateTest, TestDateFromYMD) {
    Year y = 2018;
    Month m = November;
    Day d = 22;
    Date date(y, m, d);
    ASSERT_EQ(date.year(), y);
    ASSERT_EQ(date.month(), m);
    ASSERT_EQ(date.dayOfMonth(), d);
}

TEST(DateTest, TestDateFromStr) {
    Date date("2018-11-22");
    ASSERT_EQ(date.year(), 2018);
    ASSERT_EQ(date.month(), November);
    ASSERT_EQ(date.dayOfMonth(), 22);
}

TEST(DateTest, TestDateComparison) {
    Date date1(2018, November, 12);
    Date date2(2018, November, 22);

    ASSERT_TRUE(date1 < date2);
    ASSERT_TRUE(date1 <= date2);
    ASSERT_FALSE(date1 >= date2);
    ASSERT_TRUE(date1 != date2);

    date2 = date1;
    ASSERT_TRUE(date1 == date2);
}

