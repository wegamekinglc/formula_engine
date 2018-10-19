#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

namespace FEngine {
    using std::string;
    using std::map;
    using std::vector;
    using std::shared_ptr;
    using DateTime = string;
    using Depends = map<string, vector<DateTime>>;
    using DataPack = map<string, map<string, map<DateTime, double>>>;

    Depends mergeDepends(const Depends& lhs, const Depends& rhs);
}