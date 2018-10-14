#pragma once

#include <string>
#include <map>
#include <vector>

namespace FEngine {
    using std::string;
    using std::map;
    using std::vector;
    using DateTime = string;
    using Depends = map<string, vector<DateTime>>;
    using DataPack = map<string, map<string, map<DateTime, double>>>;
}