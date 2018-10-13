#pragma once

#include "types.hpp"
#include "containers.hpp"

namespace FEngine {

    class Node {
        public:
            virtual ~Node() = 0;
            virtual Depends dependes(const DateTime& base) const = 0;
            virtual Series calculate(const DataPack& data, const DateTime& base) const = 0;
    };

    class Last: public Node {
        public:
            Last(const std::string& name): name_(name) {}
            Depends depends(const DateTime& base) const;
            Series calculate(const DataPack& data, const DateTime& base) const;
            const string& name() const { return name_;}

        private:
            string name_;
    };
}