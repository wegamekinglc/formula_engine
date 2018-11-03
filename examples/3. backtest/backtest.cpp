#include <iostream>
#include <fel/fel.hpp>

using namespace std;
using namespace FEngine;

int main() {

    // Input
    auto formula1 = (CLOSE() + OPEN()) / ( HIGH() + LOW());
    auto formula2 = CSRank(formula1);
    vector<string> codes = {"1", "600000", "600519"};
    vector<Date> dates = {Date("2018-09-06"), Date("2018-09-07"), Date("2018-09-10"), Date("2018-09-11")};

    // strategy running structure
    vector<string> fields = formula2.depends();
    PGStore store("host=localhost user=postgres password=we083826 dbname=stocks");
    map<Date, DataPack> factor_data = store.fetch_data_packs(codes, dates, fields);
    map<Date, Series> returns = store.fetch_returns_series(codes, dates, 0, 1);

    cout << "portfolio returns: " << endl;
    for(auto pair: factor_data) {
        GlobalSymbols symbols(codes);
        auto date = pair.first;
        auto pack = pair.second;
        Series alpha = formula2.calculate(pack, date);
        Series pos = alpha / sum(abs(alpha));
        Series ret = returns[date];
        double port_ret = dot(pos, ret);
        cout << date << " - " << port_ret * 100 << "%" << endl;
    }

    return 0;
}