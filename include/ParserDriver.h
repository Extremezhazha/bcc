//
// Created by zhazha on 8/29/23.
//

#ifndef BCC_PARSERDRIVER_H
#define BCC_PARSERDRIVER_H

#include <memory>
#include "ast/ASTNode.h"
#include "ASTNodeAcceptor.h"

namespace bccparse {
    class BccLexer;
    class BccParser;

    class ParserDriver : public bcc::ASTNodeAcceptor{

    public:
        ParserDriver(bcc::ASTNodeAcceptor & acceptor);
        ~ParserDriver();

        void parseString(std::string const & data);
    private:
        std::unique_ptr<BccLexer> lexer;
        std::unique_ptr<BccParser> bccParser;
        bcc::ASTNodeAcceptor & acceptor;

        friend class BccParser;

        friend class BccLexer;

    public:
        virtual void emit(bcc::AST::node_ptr_t value) override;

        virtual void emitPrint(bcc::AST::node_ptr_t value) override;
    };
} // bcc

#endif //BCC_PARSERDRIVER_H
