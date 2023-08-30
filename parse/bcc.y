%{
#include <iostream>
#include <string>
#include <memory>
#include <cmath>

#include "ast/ASTNode.h"
#include "ast/nodes/Literal.h"
#include "ast/nodes/ID.h"
#include "ast/nodes/BinaryArithmeticOperator.h"


#include "BccParser.h"
#include "BccLexer.h"

#define yylex parseDriver.lexer->yylex
%}

%code requires
{
  #include <iostream>
  #include "ParserDriver.h"
  #include "location.hh"
}

%code provides
{
  namespace bccparse
  {
    // Forward declaration of the Driver class
    class ParserDriver;

    inline void
    yyerror (const char* msg)
    {
      std::cerr << msg << std::endl;
    }
  }
}

%require "3.7.4"
%language "C++"
%locations
%debug
%define api.namespace {bccparse}
%define api.parser.class {BccParser}
%define api.value.type variant
%parse-param {bccparse::ParserDriver & parseDriver}
%lex-param {bccparse::ParserDriver & parseDriver}
%define parse.error verbose
%defines "BccParser.h"
%output "BccParser.cpp"


%token EOL LPAREN RPAREN
%token PRINTSTMT
%token ASSIGN
%token <std::string> ID
%token <int>  INT

%nterm <bcc::AST::node_ptr_t>  lvalexp
%nterm <bcc::AST::node_ptr_t>  rvalexp
%nterm <bcc::AST::node_ptr_t>  assign
%nterm <bcc::AST::node_ptr_t>  print

%nonassoc           ASSIGN
%left               PLUS MINUS
%left               MULTIPLY DIVIDE MODULO

%%

line: YYEOF
    | rvalexp YYEOF { parseDriver.emit($1); }
    | print YYEOF  { parseDriver.emitPrint($1); }
    | assign YYEOF { parseDriver.emit($1); }
    ;

rvalexp: INT   { $$ = std::make_unique<bcc::AST::nodes::Literal>($1); }
    | ID       { $$ = std::make_unique<bcc::AST::nodes::ID>($1); }
    | rvalexp PLUS rvalexp     { $$ = std::make_unique<bcc::AST::nodes::Add>(std::move($1), std::move($3)); }
    | rvalexp MINUS rvalexp    { $$ = std::make_unique<bcc::AST::nodes::Minus>(std::move($1), std::move($3)); }
    | rvalexp MULTIPLY rvalexp { $$ = std::make_unique<bcc::AST::nodes::Multiply>(std::move($1), std::move($3)); }
    | rvalexp DIVIDE rvalexp   { $$ = std::make_unique<bcc::AST::nodes::Divide>(std::move($1), std::move($3)); }
    | LPAREN rvalexp RPAREN        { $$ = $2; }
    ;

assign: lvalexp ASSIGN rvalexp { $$ = std::make_unique<bcc::AST::nodes::Assign>(std::move($1), std::move($3)); }

lvalexp: ID { $$ = std::make_unique<bcc::AST::nodes::ID>($1); }
    ;

print: PRINTSTMT LPAREN rvalexp RPAREN { $$ = $3; }

%%


void bccparse::BccParser::error(bccparse::location const & location, std::string const & msg) {
    std::cerr << location << ": " << msg << '\n';
}
