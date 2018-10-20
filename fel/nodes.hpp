#pragma once


#include <fel/types.hpp>
#include <fel/containers.hpp>

namespace FEngine {
    class Shift;

    class Node {
        public:
            virtual ~Node() = default;
            virtual Depends depends(const DateTime& base) const = 0;
            virtual Series calculate(const DataPack& data, const DateTime& base) const = 0;
            virtual Node* clone() const = 0;
            Shift operator[](unsigned int n) const;
            Shift shift(unsigned int n) const;
    };

    class Last: public Node {
        public:
            Last(const std::string& name): name_(name) {}
            Depends depends(const DateTime& base) const;
            Series calculate(const DataPack& data, const DateTime& base) const;
            const string& name() const { return name_;}
            Last* clone() const;

        private:
            string name_;
    };

    class Shift: public Node {
        public:
            Shift(const Node& inner, unsigned int n);
            Depends depends(const DateTime& base) const;
            Series calculate(const DataPack& data, const DateTime& base) const;
            Shift* clone() const;
            unsigned int period() const { return n_;}
        
        private:
            shared_ptr<Node> inner_;
            unsigned int n_;
    };

    class BinaryOperator: public Node {
        public:
            BinaryOperator(const Node& lhs, const Node& rhs);
            Depends depends(const DateTime& base) const;

        protected:
            shared_ptr<Node> lhs_;
            shared_ptr<Node> rhs_;
    };

    class PlusOperator: public BinaryOperator {
        public:
            PlusOperator(const Node& lhs, const Node& rhs);
            Series calculate(const DataPack& data, const DateTime& base) const;
            PlusOperator* clone() const;
    };

    class MinusOperator: public BinaryOperator {
        public:
            MinusOperator(const Node& lhs, const Node& rhs);
            Series calculate(const DataPack& data, const DateTime& base) const;
            MinusOperator* clone() const;
    };

    class MultiplyOperator: public BinaryOperator {
        public:
            MultiplyOperator(const Node& lhs, const Node& rhs);
            Series calculate(const DataPack& data, const DateTime& base) const;
            MultiplyOperator* clone() const;
    };

    class DivideOperator: public BinaryOperator {
        public:
            DivideOperator(const Node& lhs, const Node& rhs);
            Series calculate(const DataPack& data, const DateTime& base) const;
            DivideOperator* clone() const;
    };

    PlusOperator operator+(const Node&, const Node&);

    MinusOperator operator-(const Node&, const Node&);

    MultiplyOperator operator*(const Node&, const Node&);

    DivideOperator operator/(const Node&, const Node&);
}