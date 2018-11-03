#pragma once
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include <map>
#include <fel/utilities/containers.hpp>
#include <fel/time/date.hpp>

namespace FEngine {
    class PGStore {
        public:
            PGStore(const std::string& conn);
            pqxx::result query(const std::string& statement);
            pqxx::result fetch_factors(const std::vector<std::string>& codes,
                                       const std::vector<Date>& dates,
                                       const std::vector<std::string>& fields);
            pqxx::result fetch_returns(const std::vector<std::string>& codes,
                                       const std::vector<Date>& dates,
                                       unsigned int offset = 1,
                                       unsigned int horizon = 1);
            std::map<Date, DataPack> fetch_data_packs(const std::vector<std::string>& codes,
                                                      const std::vector<Date>& dates,
                                                      const std::vector<std::string>& fields);
            std::map<Date, Series> fetch_returns_series(const std::vector<std::string>& codes,
                                                        const std::vector<Date>& dates,
                                                        unsigned int offset = 1,
                                                        unsigned int horizon = 1);

        private:
            pqxx::connection conn_;
    };
}