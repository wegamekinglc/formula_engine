#include <fel/fel.hpp>
#include <random>
#include <iostream>

using namespace FEngine;
using namespace std;

void print(const Series& res, const DateTime& date) {
    cout << date << ": ";
    for(Series::const_iterator it=res.begin(); it != res.end(); ++it) {
        cout << it->first << ", " << it->second << ".";
    }
    cout << endl;
}

int main() {

    auto formula1 = (CLOSE() + OPEN()) / ( HIGH() + LOW());
    auto formula2 = CSRank(formula1);

    /*
    The Following are only for demonstration
    */

    vector<DateTime> dates = {"2018-01-01", "2018-02-01", "2018-03-01", "2018-04-01", "2018-05-01", "2018-06-01"};
    default_random_engine e(551);

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
        print(res1, date);
        print(res2, date);
    }

    return 0;
}