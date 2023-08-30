#ifndef BCC_LITERAL_H
#define BCC_LITERAL_H
#include <variant>

#include "../ASTNode.h"

namespace bcc::AST::nodes {

    class Literal : public ASTNode{
    private:
        using internal_t = std::variant<int>;
        internal_t value;
    public:
        explicit Literal(int value);

        void gen(term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) override;

        int forceGet();
    };

} // nodes

#endif //BCC_LITERAL_H
