#include <random>
#include <fel/settings.hpp>
#include <fel/crosssections.hpp>
#include <gtest/gtest.h>

using namespace FEngine;

TEST(CrossSectionsTest, TestCSRank) {
    auto formula1 = (Last("close") + Last("open")) / (Last("high") + Last("low"));
    auto formula2 = CSRank(formula1);

    vector<DateTime> dates = {"2018-01-01", "2018-02-01", "2018-03-01", "2018-04-01", "2018-05-01", "2018-06-01"};
    std::default_random_engine e(551);

    for(auto date: dates) {
        vector<string> s = {"aapl", "ibm", "goog", "baba"};
        GlobalSymbols symbols(s);

        Depends dep = formula1.depends(date);

        // random generated the data
        DataPack data;
        for(auto s: Settings::instance().symbols()) {
            data[s] = map<string, map<DateTime, double>>();
            for(Depends::const_iterator it=dep.begin(); it != dep.end(); ++it) {
                string name = it->first;
                data[s][name] = map<DateTime, double>();
                for(auto d: it->second)
                    data[s][name][d] = e();
            }
        }
        Series res1 = formula1.calculate(data, date);
        Series res2 = formula2.calculate(data, date);
        ASSERT_EQ(rank(res1), res2);
    }

}