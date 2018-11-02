#include <ostream>
#include <fel/data/pgstore.hpp>

namespace FEngine {
    PGStore::PGStore(const std::string& conn)
        :conn_(conn) {}

    pqxx::result PGStore::query(const std::string& statement) {
        pqxx::work worker(conn_);
        return worker.exec(statement);
    }

    pqxx::result PGStore::fetch_factors(const std::vector<int>& codes, const std::vector<Date>& dates, const std::vector<std::string>& fields) {
        pqxx::work worker(conn_);
        std::string statement = "select trade_date, code";
        for(auto field: fields)
            statement += ", " + field;
        statement += " from eqy_stock_eod where code in (";
        for(auto i = codes.begin();;) {
            statement += std::to_string(*i);
            ++i;
            if(i == codes.end())
                break;
            statement += ", ";
        }
        statement += ") and trade_date in (";
        for(auto i = dates.begin();;) {
            std::ostringstream convert;
            convert << *i;
            statement += worker.quote(convert.str());
            ++i;
            if(i == dates.end())
                break;
            statement += ", ";
        }
        statement += ") order by trade_date, code;";
        return worker.exec(statement);
    }
}
