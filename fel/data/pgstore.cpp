#include <fel/data/pgstore.hpp>
#include <iostream>

namespace FEngine {
    PGStore::PGStore(const String_& conn)
        :conn_(conn) {}

    pqxx::result PGStore::fetch_data_internal(const Vector_<String_>& codes,
                                              const Vector_<Date>& dates,
                                              const Vector_<String_>& fields,
                                              String_ table) {
        pqxx::work worker(conn_);
        String_ statement = "select trade_date, code";
        for(const auto &field: fields)
            statement += ", \"" + field + "\"";
        statement += " from " + table + " where code in (";
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

    pqxx::result PGStore::fetch_market(const Vector_<String_>& codes, const Vector_<Date>& dates, const Vector_<String_>& fields) {
        return fetch_data_internal(codes, dates, fields, "market");
    }

    pqxx::result PGStore::fetch_factors(const Vector_<String_>& codes, const Vector_<Date>& dates, const Vector_<String_>& fields) {
        return fetch_data_internal(codes, dates, fields, "uqer");
    }

    pqxx::result PGStore::fetch_returns(const Vector_<String_>& codes, const Vector_<Date>& dates, unsigned int offset, unsigned int horizon) {
        pqxx::work worker(conn_);
        Date first_date = dates[0];
        Date last_date = dates[dates.size()-1];
        unsigned int first_row = offset;
        unsigned int last_row = offset + horizon - 1;
        String_ statement = "select trade_date, code, sum(ln(1. + \"chgPct\")) over (partition by code order by trade_date rows between ";
        statement += std::to_string(first_row) + " following and " + std::to_string(last_row) + " following ) as dx from market where ";
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
        statement += ") order by trade_date, code";
        statement = "select * from (" + statement + ") t where t.trade_date in (";
        for(auto i = dates.begin();;) {
            statement += worker.quote(Date::to_string(*i));
            ++i;
            if(i == dates.end())
                break;
            statement += ", ";
        }
        statement += ");";
        return worker.exec(statement);
    }

    Map_<Date, DataPack> PGStore::fetch_data_packs(const Vector_<String_>& codes, const Vector_<Date>& dates, const Vector_<String_>& fields) {
        pqxx::result r = fetch_factors(codes, dates, fields);
        pqxx::result::const_iterator it = r.begin();
        Map_<Date, DataPack> res;
    
        for(auto date: dates) {
            DataPack data;
            while(it != r.end()) {
                if(Date((*it)["trade_date"].c_str()) != date)
                    break;
                String_ s = (*it)["code"].c_str();
                if(data.find(s) == data.end())
                    data[s] = Map_<String_, Map_<DateTime, double>>();
                for(const auto &f: fields) {
                    String_ escaped = "\""+ f + "\"";
                    if(data[s].find(escaped) == data[s].end())
                        data[s][f] = Map_<DateTime, double>();
                    data[s][f][date] = (*it)[escaped].as<double>();
                }
                ++it;
                if(it == r.end() || Date((*it)["trade_date"].c_str()) != date )
                    break;
            }
            res[date] = data;
        }
        return res;
    }

    Map_<Date, Series> PGStore::fetch_returns_series(const Vector_<String_>& codes, const Vector_<Date>& dates, unsigned int offset, unsigned int horizon) {
        pqxx::result r = fetch_returns(codes, dates, offset, horizon);
        pqxx::result::const_iterator it = r.begin();
        Map_<Date, Series> res;

        for(auto date: dates) {
            Vector_<String_> symbols;
            Vector_<double> vals;
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

    String_ PGStore::query_universe(String_ name, const Vector_<Date>& dates) const {
        return String_();
    }
}
