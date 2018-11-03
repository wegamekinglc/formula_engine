#pragma once

#include<fel/types.hpp>
#include<fel/operators/nodes.hpp>

namespace FEngine {

    class CSBase: public Node {
        public:
            explicit CSBase(const Node& inner);
            Depends depends(const DateTime& base) const override;
            std::vector<std::string> depends() const override;
        
        protected:
            shared_ptr<Node> inner_;
    };

    class CSRank: public CSBase {
        public:
            explicit CSRank(const Node& inner);
            Series calculate(const DataPack& data, const DateTime& base) const override;
            CSRank* clone() const override;
    };
}