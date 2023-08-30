%{
#include <cstdlib>
#include "ast/ASTNode.h"

#include "BccParser.h"
#include "BccLexer.h"
#include "ParserDriver.h"
using namespace bccparse;
%}

%option debug
%option c++
%option noyywrap
%option never-interactive
%option yylineno
%option nounput
%option batch
%option prefix="bccparse"


integer          ([[:digit:]]+)
idpattern        ([_a-zA-Z][_a-zA-Z0-9]*)

%%
print       return BccParser::token::PRINTSTMT;
{integer}   yylval->emplace<int>(strtoll(yytext, nullptr, 10)); return BccParser::token::INT;
{idpattern} yylval->emplace<std::string>(std::string{yytext}); return BccParser::token::ID;
"+"         return BccParser::token::PLUS;
"-"         return BccParser::token::MINUS;
"*"         return BccParser::token::MULTIPLY;
"/"         return BccParser::token::DIVIDE;
"("         return BccParser::token::LPAREN;
")"         return BccParser::token::RPAREN;
"="         return BccParser::token::ASSIGN;
\n          return BccParser::token::EOL;
<<EOF>>     return BccParser::token::YYEOF;
.           /* no action on unmatched input */

%%

namespace bccparse
{

    BccLexer::BccLexer()
    : bccparseFlexLexer()
    {
    }

    BccLexer::~BccLexer()
    {
    }

    void BccLexer::set_debug(bool b)
    {
        yy_flex_debug = b;
    }
}

#ifdef yylex
# undef yylex
#endif

int bccparseFlexLexer::yylex() {
  return 0;
}