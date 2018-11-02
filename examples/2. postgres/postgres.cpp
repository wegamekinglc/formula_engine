#include <iostream>
#include <fel/fel.hpp>

using namespace FEngine;

int main()
{
    PGStore store("host=localhost user=postgres password=we083826 dbname=stocks");
    std::vector<int> codes = {1, 600000};
    std::vector<Date> dates = {Date("2018-09-10"), Date("2018-09-11")};
    std::vector<std::string> fields = {"openprice", "closeprice"};

    pqxx::result R = store.fetch_factors(codes, dates, fields);

    std::cout << "Found " << R.size() << "employees:" << std::endl;
    for (auto row: R)
        std::cout << row[0].c_str() << ", " << row[1].c_str() << std::endl;
    return 0;
}