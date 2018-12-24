#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <fel/time/date.hpp>

namespace FEngine {
    using String_ = std::string;
    template<typename S, typename T>
    using Map_ = std::map<S, T>;
    template<typename V>
    using Vector_ = std::vector<V>;
    using std::shared_ptr;
    using DateTime = Date;
    using Depends = Map_<String_, Vector_<DateTime>>;
    using DataPack = Map_<String_, Map_<String_, Map_<DateTime, double>>>;

    Depends mergeDepends(const Depends& lhs, const Depends& rhs);
}