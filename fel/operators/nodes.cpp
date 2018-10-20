#include <fel/operators/nodes.hpp>
#include <fel/settings.hpp>

namespace FEngine {

    Shift Node::shift(unsigned int n) const {
        return Shift(*this, n);
    }

    Shift Node::operator[](unsigned int n) const {
        return shift(n);
    }

    Depends Last::depends(const DateTime& base) const {
        vector<DateTime> dts(1, base);
        Depends res;
        res[name_] = dts;
        return res;
    }

    Series Last::calculate(const DataPack& data, const DateTime& base) const {
        const vector<string>& symbols = Settings::instance().symbols();
        vector<double> values(symbols.size());
        for(size_t i = 0; i != symbols.size(); ++i) {
            values[i] = data.at(symbols[i]).at(name_).at(base);
        }
        return Series(symbols, values);
    }

    Last* Last::clone() const {
        return new Last(name_);
    }

    Shift::Shift(const Node& inner, unsigned int n)
        :inner_(inner.clone()), n_(n) {}

    Depends Shift::depends(const DateTime& base) const {
        // currenctly the implementation is not correct
        Depends res = inner_->depends(base);
        return res;
    }

    Shift* Shift::clone() const {
        return new Shift(*inner_, n_);
    }

    Series Shift::calculate(const DataPack& data, const DateTime& base) const {
        // currenctly the implementation is not correct
        return inner_->calculate(data, base);
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

    MinusOperator::MinusOperator(const Node& lhs, const Node& rhs)
        :BinaryOperator(lhs, rhs) {}

    Series MinusOperator::calculate(const DataPack& data, const DateTime& base) const {
        Series lres = lhs_->calculate(data, base);
        Series rres = rhs_->calculate(data, base);
        return lres - rres;
    }

    MinusOperator* MinusOperator::clone() const {
        return new MinusOperator(*lhs_, *rhs_);
    }

    MinusOperator operator-(const Node& lhs, const Node& rhs) {
        return MinusOperator(lhs, rhs);
    }

    MultiplyOperator::MultiplyOperator(const Node& lhs, const Node& rhs)
        :BinaryOperator(lhs, rhs) {}

    Series MultiplyOperator::calculate(const DataPack& data, const DateTime& base) const {
        Series lres = lhs_->calculate(data, base);
        Series rres = rhs_->calculate(data, base);
        return lres * rres;
    }

    MultiplyOperator* MultiplyOperator::clone() const {
        return new MultiplyOperator(*lhs_, *rhs_);
    }

    MultiplyOperator operator*(const Node& lhs, const Node& rhs) {
        return MultiplyOperator(lhs, rhs);
    }

    DivideOperator::DivideOperator(const Node& lhs, const Node& rhs)
        :BinaryOperator(lhs, rhs) {}

    Series DivideOperator::calculate(const DataPack& data, const DateTime& base) const {
        Series lres = lhs_->calculate(data, base);
        Series rres = rhs_->calculate(data, base);
        return lres / rres;
    }

    DivideOperator* DivideOperator::clone() const {
        return new DivideOperator(*lhs_, *rhs_);
    }

    DivideOperator operator/(const Node& lhs, const Node& rhs) {
        return DivideOperator(lhs, rhs);
    }
}