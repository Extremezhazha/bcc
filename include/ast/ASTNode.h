
#ifndef BCC_ASTNODE_H
#define BCC_ASTNODE_H

#include <vector>
#include <memory>
#include <map>

#include "../eval/Term.h"

namespace bcc::AST {
    class ASTNode {
    protected:
        using node_vec_t = std::vector<std::shared_ptr<ASTNode>>;
        using term_vec_t = std::vector<std::unique_ptr<bcc::Term>>;
        using term_ptr_t = std::unique_ptr<bcc::Term>;
    public:
        virtual void gen(term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) = 0;
    };

    using node_ptr_t = std::shared_ptr<ASTNode>;
}


#endif //BCC_ASTNODE_H
