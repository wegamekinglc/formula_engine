#pragma once

#include <fel/time/date.hpp>

namespace FEngine {
    class DateParser {
      public:
        static Date parseISO(const std::string& str);
    };
}