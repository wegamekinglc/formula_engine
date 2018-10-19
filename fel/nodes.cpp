#include <fel/nodes.hpp>
#include <fel/settings.hpp>

namespace FEngine {

    Depends Last::depends(const DateTime& base) const {
        vector<DateTime> dts(1, base);
        Depends res;
        res[name_] = dts;
        return res;
    }

    Series Last::calculate(const DataPack& data, const DateTime& base) const {
        vector<string> symbols = Settings::instance().symbols();
        vector<double> values(symbols.size());
        for(size_t i = 0; i != symbols.size(); ++i) {
            values[i] = data.at(symbols[i]).at(name_).at(base);
        }
        return Series(symbols, values);
    }

    Last* Last::clone() const {
        return new Last(name_);
    }

    BinaryOperator::BinaryOperator(const Node& lhs, const Node& rhs)
        :lhs_(lhs.clone()), rhs_(rhs.clone()) {}

    Depends BinaryOperator::depends(const DateTime& base) const {
        Depends ldep = lhs_->depends(base);
        Depends rdep = rhs_->depends(base);
        return mergeDepends(ldep, rdep);
    }

    PlusOperator::PlusOperator(const Node& lhs, const Node& rhs)
        :BinaryOperator(lhs, rhs) {}

    Series PlusOperator::calculate(const DataPack& data, const DateTime& base) const {
        Series lres = lhs_->calculate(data, base);
        Series rres = rhs_->calculate(data, base);
        return lres + rres;
    }

    PlusOperator* PlusOperator::clone() const {
        return new PlusOperator(*lhs_, *rhs_);
    }

    PlusOperator operator+(const Node& lhs, const Node& rhs) {
        return PlusOperator(lhs, rhs);
    }
}