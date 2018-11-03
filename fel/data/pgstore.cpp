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
            statement += worker.quote(Date::to_string(*i));
            ++i;
            if(i == dates.end())
                break;
            statement += ", ";
        }
        statement += ") order by trade_date, code;";
        return worker.exec(statement);
    }

    pqxx::result PGStore::fetch_returns(const std::vector<int>& codes, const std::vector<Date>& dates, unsigned int offset, unsigned int horizon) {
        pqxx::work worker(conn_);
        Date first_date = dates[0];
        Date last_date = dates[dates.size()-1];
        unsigned int first_row = offset;
        unsigned int last_row = offset + horizon - 1;
        std::string statement = "select trade_date, code, chgpct, sum(ln(1. + chgpct)) over (partition by code order by trade_date rows between ";
        statement += std::to_string(first_row) + " following and " + std::to_string(last_row) + " following ) as dx from eqy_stock_eod where ";
        statement += "trade_date between " + worker.quote(Date::to_string(first_date)) + " and ";
        statement +=  worker.quote(Date::to_string(last_date)) + " and ";
        statement += "code in (";
        for(auto i = codes.begin();;) {
            statement += std::to_string(*i);
            ++i;
            if(i == codes.end())
                break;
            statement += ", ";
        }
        statement += ");";
        return worker.exec(statement);
    }
}
