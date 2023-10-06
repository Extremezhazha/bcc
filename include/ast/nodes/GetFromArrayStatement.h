#ifndef BCC_GETFROMARRAYSTATEMENT_H
#define BCC_GETFROMARRAYSTATEMENT_H
#include "ast/ASTNode.h"

namespace bcc::AST::nodes {

    class GetFromArrayStatement : public ASTNode {
    private:
        node_ptr_t data;
        node_ptr_t index;
    public:
        GetFromArrayStatement(node_ptr_t data, node_ptr_t index);

        void gen(term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) override;
    };

} // nodes

#endif //BCC_GETFROMARRAYSTATEMENT_H
