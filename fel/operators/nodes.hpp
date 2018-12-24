#pragma once


#include <fel/types.hpp>
#include <fel/utilities/containers.hpp>

namespace FEngine {
    class Shift;

    class Node {
        public:
            virtual ~Node() = default;
            virtual Depends depends(const DateTime& base) const = 0;
            virtual std::vector<String_> depends() const = 0;
            virtual Series calculate(const DataPack& data, const DateTime& base) const = 0;
            virtual Node* clone() const = 0;
            Shift operator[](unsigned int n) const;
            Shift shift(unsigned int n) const;
    };

    class Last: public Node {
        public:
            explicit Last(String_ name): name_(std::move(name)) {}
            Depends depends(const DateTime& base) const override;
            std::vector<String_> depends() const override;
            Series calculate(const DataPack& data, const DateTime& base) const override;
            const String_& name() const { return name_;}
            Last* clone() const override;

        private:
            String_ name_;
    };

    class Shift: public Node {
        public:
            Shift(const Node& inner, unsigned int n);
            Depends depends(const DateTime& base) const override;
            std::vector<String_> depends() const override;
            Series calculate(const DataPack& data, const DateTime& base) const override;
            Shift* clone() const override;
            unsigned int period() const { return n_;}
        
        private:
            shared_ptr<Node> inner_;
            unsigned int n_;
    };

    class BinaryOperator: public Node {
        public:
            BinaryOperator(const Node& lhs, const Node& rhs);
            Depends depends(const DateTime& base) const override;
            std::vector<String_> depends() const override;

        protected:
            shared_ptr<Node> lhs_;
            shared_ptr<Node> rhs_;
    };

    class PlusOperator: public BinaryOperator {
        public:
            PlusOperator(const Node& lhs, const Node& rhs);
            Series calculate(const DataPack& data, const DateTime& base) const override;
            PlusOperator* clone() const override;
    };

    class MinusOperator: public BinaryOperator {
        public:
            MinusOperator(const Node& lhs, const Node& rhs);
            Series calculate(const DataPack& data, const DateTime& base) const override;
            MinusOperator* clone() const override;
    };

    class MultiplyOperator: public BinaryOperator {
        public:
            MultiplyOperator(const Node& lhs, const Node& rhs);
            Series calculate(const DataPack& data, const DateTime& base) const override;
            MultiplyOperator* clone() const override;
    };

    class DivideOperator: public BinaryOperator {
        public:
            DivideOperator(const Node& lhs, const Node& rhs);
            Series calculate(const DataPack& data, const DateTime& base) const override;
            DivideOperator* clone() const override;
    };

    PlusOperator operator+(const Node&, const Node&);

    MinusOperator operator-(const Node&, const Node&);

    MultiplyOperator operator*(const Node&, const Node&);

    DivideOperator operator/(const Node&, const Node&);
}