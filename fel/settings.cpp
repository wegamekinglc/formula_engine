#include <fel/settings.hpp>

namespace FEngine {
    DateTime Settings::referenceDate() const {
        return referenceDate_;
    }

    void Settings::setReferenceDate(const DateTime& dt) {
        referenceDate_ = dt;
    }

    const Vector_<String_>& Settings::symbols() const {
        return symbols_;
    }

    void Settings::setSymbols(const Vector_<String_>& symbols) {
        symbols_ = symbols;
    }

    GlobalSymbols::GlobalSymbols(const Vector_<String_>& symbols) {
        preSymbols_ = Settings::instance().symbols();
        Settings::instance().setSymbols(symbols);
    }

    GlobalSymbols::~GlobalSymbols() {
        Settings::instance().setSymbols(preSymbols_);
    }
}