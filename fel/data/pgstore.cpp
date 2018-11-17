#include <fel/data/pgstore.hpp>
#include <iostream>

namespace FEngine {
    PGStore::PGStore(const std::string& conn)
        :conn_(conn) {}

    pqxx::result PGStore::query(const std::string& statement) {
        pqxx::work worker(conn_);
        return worker.exec(statement);
    }

    pqxx::result PGStore::fetch_factors(const std::vector<std::string>& codes, const std::vector<Date>& dates, const std::vector<std::string>& fields) {
        pqxx::work worker(conn_);
        std::string statement = "select trade_date, code";
        for(auto field: fields)
            statement += ", " + field;
        statement += " from uqer where code in (";
        for(auto i = codes.begin();;) {
            statement += *i;
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

    pqxx::result PGStore::fetch_returns(const std::vector<std::string>& codes, const std::vector<Date>& dates, unsigned int offset, unsigned int horizon) {
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
            statement += *i;
            ++i;
            if(i == codes.end())
                break;
            statement += ", ";
        }
        statement += ") order by trade_date, code;";
        return worker.exec(statement);
    }

    std::map<Date, DataPack> PGStore::fetch_data_packs(const std::vector<std::string>& codes, const std::vector<Date>& dates, const std::vector<std::string>& fields) {
        pqxx::result r = fetch_factors(codes, dates, fields);
        pqxx::result::const_iterator it = r.begin();
        std::map<Date, DataPack> res;
    
        for(auto date: dates) {
            DataPack data;
            while(it != r.end()) {
                if(Date((*it)["trade_date"].c_str()) != date)
                    break;
                std::string s = (*it)["code"].c_str();
                if(data.find(s) == data.end())
                    data[s] = map<string, map<DateTime, double>>();
                for(auto f: fields) {
                    if(data[s].find(f) == data[s].end())
                        data[s][f] = map<DateTime, double>();
                    data[s][f][date] = (*it)[f].as<double>();
                }
                ++it;
                if(it == r.end() || Date((*it)["trade_date"].c_str()) != date )
                    break;
            }
            res[date] = data;
        }
        return res;
    }

    std::map<Date, Series> PGStore::fetch_returns_series(const std::vector<std::string>& codes, const std::vector<Date>& dates, unsigned int offset, unsigned int horizon) {
        pqxx::result r = fetch_returns(codes, dates, offset, horizon);
        pqxx::result::const_iterator it = r.begin();
        std::map<Date, Series> res;

        for(auto date: dates) {
            std::vector<std::string> symbols;
            std::vector<double> vals;
            while(it != r.end() && Date((*it)["trade_date"].c_str()) == date) {
                symbols.push_back((*it)["code"].c_str());
                vals.push_back((*it)["dx"].as<double>());
                ++it;
            }
            if(!symbols.empty())
                res[date] = Series(symbols, vals); 
        }
        return res;
    }
}
