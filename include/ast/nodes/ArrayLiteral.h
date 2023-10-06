#ifndef BCC_ARRAYLITERAL_H
#define BCC_ARRAYLITERAL_H

#include "ast/ASTNode.h"
#include <vector>

namespace bcc::AST::nodes {

    class ArrayLiteral : public ASTNode {
    private:
        std::vector<node_ptr_t> values;

    public:

        explicit ArrayLiteral(std::vector<node_ptr_t> values);

        void gen(term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) override;

    };

} // nodes

#endif //BCC_ARRAYLITERAL_H
