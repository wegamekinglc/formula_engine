#pragma once

#include<fel/types.hpp>
#include<fel/nodes.hpp>

namespace FEngine {

    class CSBase: public Node {
        public:
            CSBase(const Node& inner);
            Depends depends(const DateTime& base) const;
        
        protected:
            shared_ptr<Node> inner_;
    };

    class CSRank: public CSBase {
        public:
            CSRank(const Node& inner);
            Series calculate(const DataPack& data, const DateTime& base) const;
            CSRank* clone() const;
    };
}