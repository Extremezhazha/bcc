#include "ast/nodes/GetFromArrayStatement.h"
#include "eval/arrays/GetFromArray.h"

namespace bcc::AST::nodes {
    GetFromArrayStatement::GetFromArrayStatement(node_ptr_t data, node_ptr_t index) : data{std::move(data)}, index{std::move(index)} {}

    void GetFromArrayStatement::gen(ASTNode::term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) {
        data->gen(output, varSSAMap, false);
        index->gen(output, varSSAMap, false);
        term_ptr_t indexGenerated = std::move(output.back());
        output.pop_back();
        term_ptr_t dataGenerated = std::move(output.back());
        output.pop_back();

        output.emplace_back(std::make_unique<arrays::GetFromArray>(std::move(indexGenerated), std::move(dataGenerated)));
    }
} // nodes