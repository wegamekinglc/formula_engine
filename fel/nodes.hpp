#pragma once


#include <fel/types.hpp>
#include <fel/containers.hpp>

namespace FEngine {

    class Node {
        public:
            virtual ~Node() = default;
            virtual Depends depends(const DateTime& base) const = 0;
            virtual Series calculate(const DataPack& data, const DateTime& base) const = 0;
            virtual Node* clone() const = 0;
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

    PlusOperator operator+(const Node&, const Node&);

    
}