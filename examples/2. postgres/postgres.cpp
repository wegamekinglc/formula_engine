#include <iostream>
#include <fel/fel.hpp>

using namespace FEngine;

int main()
{
    PGStore store("host=localhost user=postgres password=we083826 dbname=stocks");
    std::vector<int> codes = {1, 600000};
    std::vector<Date> dates = {Date("2018-09-10"), Date("2018-09-11")};
    std::vector<std::string> fields = {"openprice", "closeprice"};

    pqxx::result r1 = store.fetch_factors(codes, dates, fields);

    std::cout << "Found " << r1.size() << " records:" << std::endl;
    for (auto row: r1)
        std::cout << row[0].c_str() << ", " << row[1].c_str() << std::endl;

    pqxx::result r2 = store.fetch_returns(codes, dates, 0, 1);
    for (auto row: r2)
        std::cout << row[0].c_str() << ", " << row[1].c_str() << ", " << row[2].c_str() << std::endl;
    return 0;
}