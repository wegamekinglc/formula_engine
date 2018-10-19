#include<fel/crosssections.hpp>

namespace FEngine {

    CSBase::CSBase(const Node& inner)
        :inner_(inner.clone()) {}

    Depends CSBase::depends(const DateTime& base) const {
        return inner_->depends(base);
    }

    CSRank* CSRank::clone() const {
        return new CSRank(*inner_);
    }
}