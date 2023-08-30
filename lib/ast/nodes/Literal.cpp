//
// Created by zhazha on 8/29/23.
//

#include "ast/nodes/Literal.h"
#include "eval/IntegerConstant.h"

namespace bcc::AST::nodes {
    Literal::Literal(int value) : value{value} {}

    void Literal::gen(term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) {
        std::visit([&](int intValue) {
            output.emplace_back(std::make_unique<bcc::IntegerConstant>(intValue));
        }, value);
    }

    int Literal::forceGet() {
        return std::visit([&](int intValue) {
            return intValue;
        }, value);
    }
} // nodes