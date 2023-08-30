#ifndef BCC_BINARYARITHMETICOPERATOR_H
#define BCC_BINARYARITHMETICOPERATOR_H

#include <utility>

#include "ast/ASTNode.h"
#include "eval/operators/Add.h"
#include "eval/operators/Minus.h"
#include "eval/operators/Multiply.h"
#include "eval/operators/Divide.h"
#include "eval/Assignment.h"

namespace bcc::AST::nodes {
    namespace impl {
        template <typename T, bool lhsIsLvalue>
        class BinaryArithmeticOperator : public ASTNode {
        private:
            node_ptr_t lhs;
            node_ptr_t rhs;
        public:
            void gen(term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) override {
                rhs->gen(output, varSSAMap, false);
                lhs->gen(output, varSSAMap, lhsIsLvalue);
                term_ptr_t lhsGenerated = std::move(output.back());
                output.pop_back();
                term_ptr_t rhsGenerated = std::move(output.back());
                output.pop_back();
                output.emplace_back(std::make_unique<T>(std::move(lhsGenerated), std::move(rhsGenerated)));
            }

            BinaryArithmeticOperator(node_ptr_t lhs, node_ptr_t rhs) : lhs{std::move(lhs)}, rhs{std::move(rhs)} {}
        };
    }

    using Add = impl::BinaryArithmeticOperator<bcc::operators::Add, false>;
    using Minus = impl::BinaryArithmeticOperator<bcc::operators::Minus, false>;
    using Multiply = impl::BinaryArithmeticOperator<bcc::operators::Multiply, false>;
    using Divide = impl::BinaryArithmeticOperator<bcc::operators::Divide, false>;
    using Assign = impl::BinaryArithmeticOperator<bcc::Assignment, true>;
}

#endif //BCC_BINARYARITHMETICOPERATOR_H
