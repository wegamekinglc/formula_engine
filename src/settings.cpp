#include "settings.hpp"

namespace FEngine {
    DateTime Settings::referenceDate() const {
        return referenceDate_;
    }

    void Settings::setReferenceDate(const DateTime& dt) {
        referenceDate_ = dt;
    }
}