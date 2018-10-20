#include <fel/time/dateparser.hpp>
#include <fel/utilities/errors.hpp>

namespace FEngine {

    namespace {

    }

    Date DateParser::parseISO(const std::string& str) {
        FEL_REQUIRE(str.size() == 10 && str[4] == '-' && str[7] == '-',
                   "invalid format");
        int year = std::atoi(str.substr(0, 4).c_str());
        Month month = static_cast<Month>(std::atoi(str.substr(5, 2).c_str()));
        int day = std::atoi(str.substr(8, 2).c_str());

        return Date(day, month, year);
    }
}