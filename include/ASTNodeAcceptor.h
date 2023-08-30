#ifndef BCC_ASTNODEACCEPTOR_H
#define BCC_ASTNODEACCEPTOR_H

#include "ast/ASTNode.h"

namespace bcc {
    class ASTNodeAcceptor {
    public:
        virtual void emit(bcc::AST::node_ptr_t value) = 0;

        virtual void emitPrint(bcc::AST::node_ptr_t value) = 0;
    };
}

#endif //BCC_ASTNODEACCEPTOR_H
