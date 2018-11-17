#include <iostream>
#include <fel/fel.hpp>

using namespace std;
using namespace FEngine;

int main() {

    // Input
    auto formula1 = (PE() - PB()) / ( PE() + PB());
    auto formula2 = CSRank(formula1);
    vector<string> codes = {"1", "600000", "600519"};

    Date start_date(2010, Sep, 6);
    China cal(China::SSE);
    vector<Date> dates;
    Date current_date = start_date;
    while(true) {
        current_date = cal.advance(current_date, Period(1 * TimeUnit::Weeks), BusinessDayConvention::Following);
        if(current_date >= Date(2018, Nov, 14))
            break;
        dates.push_back(current_date);
    }

    // strategy running structure
    vector<string> fields = formula2.depends();
    PGStore store("host=180.166.26.82 user=alpha password=alpha dbname=alpha port=8890");
    map<Date, DataPack> factor_data = store.fetch_data_packs(codes, dates, fields);
    map<Date, Series> returns = store.fetch_returns_series(codes, dates, 0, 5);

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