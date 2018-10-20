#include<fel/operators/crosssections.hpp>

namespace FEngine {

    CSBase::CSBase(const Node& inner)
        :inner_(inner.clone()) {}

    CSRank::CSRank(const Node& inner)
        :CSBase(inner) {}

    Depends CSBase::depends(const DateTime& base) const {
        return inner_->depends(base);
    }

    CSRank* CSRank::clone() const {
        return new CSRank(*inner_);
    }

    Series CSRank::calculate(const DataPack& data, const DateTime& base) const {
        Series vals = inner_->calculate(data, base);
        return rank(vals);
    }
}