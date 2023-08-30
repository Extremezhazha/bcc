//
// Created by zhazha on 8/29/23.
//

#ifndef BCC_REPLDRIVER_H
#define BCC_REPLDRIVER_H

#include <memory>
#include <vector>

#include "ast/ASTNode.h"
#include "ASTNodeAcceptor.h"
#include "ParserDriver.h"

namespace bcc {

    class REPLDriver : public ASTNodeAcceptor {
    private:
        std::unique_ptr<bccparse::ParserDriver> parserDriver;

        std::istream & inputStream;

        std::ostream & outputStream;

        std::vector<AST::node_ptr_t> instructions;

    public:
        virtual void emit(bcc::AST::node_ptr_t value) override;

        virtual void emitPrint(bcc::AST::node_ptr_t value) override;
    public:
        REPLDriver(std::istream & inputStream, std::ostream & outputStream);

        void run();
    };

} // bcc

#endif //BCC_REPLDRIVER_H
