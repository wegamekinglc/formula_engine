#include <iostream>
#include <pqxx/pqxx>

int main()
{
    try
    {
        pqxx::connection C("host=localhost user=postgres password=we083826 dbname=stocks");
        std::cout << "Connected to " << C.dbname() << std::endl;
        pqxx::work W(C);

        pqxx::result R = W.exec("SELECT code, trade_date FROM eqy_stock_eod where code = 1;");

        std::cout << "Found " << R.size() << "employees:" << std::endl;
        for (auto row: R)
            std::cout << row[0].c_str() << ", " << row[1].c_str() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}