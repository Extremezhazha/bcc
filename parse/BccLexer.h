#ifndef BCC_BCCLEXER_H
#define BCC_BCCLEXER_H

#include "BccParser.h"

# ifndef YY_DECL
#define YY_DECL \
        bccparse::BccParser::token_type bccparse::BccLexer::yylex( \
            bccparse::BccParser::semantic_type *yylval, \
            bccparse::BccParser::location_type* yylloc, \
            bccparse::ParserDriver & parserDriver)
# endif

# ifndef __FLEX_LEXER_H
#  define yyFlexLexer bccparseFlexLexer
#  include <FlexLexer.h>
#  undef yyFlexLexer
# endif

namespace bccparse
{
    class BccLexer : public bccparseFlexLexer
    {
    public:
        BccLexer();

        virtual ~BccLexer();

        virtual BccParser::token_type yylex(
                BccParser::semantic_type* yylval,
                BccParser::location_type* yylloc,
                ParserDriver & parserDriver);

        void set_debug(bool b);
    };
}

#endif //BCC_BCCLEXER_H
