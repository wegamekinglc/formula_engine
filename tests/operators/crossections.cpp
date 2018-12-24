#include <random>
#include <fel/settings.hpp>
#include <fel/operators/crosssections.hpp>
#include <gtest/gtest.h>

using namespace FEngine;

TEST(CrossSectionsTest, TestCSRank) {
    auto formula1 = (Last("close") + Last("open")) / (Last("high") + Last("low"));
    auto formula2 = CSRank(formula1);

    Vector_<DateTime> dates = {Date("2018-01-01"), Date("2018-02-01"), Date("2018-03-01"), Date("2018-04-01"), Date("2018-05-01"), Date("2018-06-01")};
    std::default_random_engine e(551);

    for(auto date: dates) {
        Vector_<String_> ss = {"aapl", "ibm", "goog", "baba"};
        GlobalSymbols symbols(ss);

        Depends dep = formula1.depends(date);

        // random generated the data
        DataPack data;
        for(const auto &s: Settings::instance().symbols()) {
            data[s] = Map_<String_, Map_<DateTime, double>>();
            for(Depends::const_iterator it=dep.begin(); it != dep.end(); ++it) {
                String_ name = it->first;
                data[s][name] = Map_<DateTime, double>();
                for(auto d: it->second)
                    data[s][name][d] = e();
            }
        }
        Series res1 = formula1.calculate(data, date);
        Series res2 = formula2.calculate(data, date);
        ASSERT_EQ(rank(res1), res2);
    }

}