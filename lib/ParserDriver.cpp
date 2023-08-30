//
// Created by zhazha on 8/29/23.
//
#include <memory>
#include <sstream>
#include "ParserDriver.h"
#include "ast/ASTNode.h"
#include "BccParser.h"
#include "BccLexer.h"
#include "ast/nodes/Literal.h"

namespace bcc {
} // bcc
bccparse::ParserDriver::ParserDriver(bcc::ASTNodeAcceptor & acceptor) :
    lexer{std::make_unique<BccLexer>()},
    bccParser{std::make_unique<BccParser>(*this)},
    acceptor{acceptor} {}


bccparse::ParserDriver::~ParserDriver() {}

void bccparse::ParserDriver::emit(bcc::AST::node_ptr_t value) {
    acceptor.emit(std::move(value));
}

void bccparse::ParserDriver::parseString(std::string const & data) {
    std::istringstream dataStream{data};
    lexer->switch_streams(&dataStream, &std::cerr);
    bccParser->parse();
}

void bccparse::ParserDriver::emitPrint(bcc::AST::node_ptr_t value) {
    acceptor.emitPrint(std::move(value));
}
