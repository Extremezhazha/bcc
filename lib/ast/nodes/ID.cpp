#include "ast/nodes/ID.h"
#include "eval/RvalVariable.h"

#include <utility>

namespace bcc::AST::nodes {
    ID::ID(std::string value) : value{std::move(value)} {}

    void ID::gen(term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) {
        int idx = isLvalue ? ++varSSAMap[value] : varSSAMap[value];
        output.emplace_back(std::make_unique<bcc::RvalVariable>(generateSSAName(idx)));
    }

    std::string ID::generateSSAName(int idx) {
        return value + "_SSA_" + std::to_string(idx);
    }
} // nodes