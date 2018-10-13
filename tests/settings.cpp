#include <fel/settings.hpp>
#include <gtest/gtest.h>

using namespace FEngine;

TEST(SettingsTest, TestReferenceDate) {
    DateTime today("2018-10-13");
    Settings::instance().setReferenceDate(today);
    ASSERT_EQ(today, Settings::instance().referenceDate());
}

TEST(SettingsTest, TestSymbols) {
    vector<string> symbols = {"a", "b"};
    Settings::instance().setSymbols(symbols);
    ASSERT_EQ(symbols, Settings::instance().symbols());
}