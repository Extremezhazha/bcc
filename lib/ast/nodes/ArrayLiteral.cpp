#include "ast/nodes/ArrayLiteral.h"
#include "eval/arrays/Array.h"

namespace bcc::AST::nodes {
    ArrayLiteral::ArrayLiteral(std::vector<node_ptr_t> values) : values{std::move(values)} {}

    void ArrayLiteral::gen(ASTNode::term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) {
        ASTNode::term_vec_t termList;
        for (auto & cur : values) {
            cur->gen(output, varSSAMap, false);
            termList.emplace_back(std::move(output.back()));
            output.pop_back();
        }
        output.emplace_back(std::make_unique<arrays::Array>(std::move(termList)));
    }


} // nodes