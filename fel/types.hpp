#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <fel/time/date.hpp>

namespace FEngine {
    using std::string;
    using std::map;
    using std::vector;
    using std::shared_ptr;
    using DateTime = Date;
    using Depends = map<string, vector<DateTime>>;
    using DataPack = map<string, map<string, map<DateTime, double>>>;

    Depends mergeDepends(const Depends& lhs, const Depends& rhs);
}