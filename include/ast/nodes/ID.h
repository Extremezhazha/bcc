//
// Created by zhazha on 8/29/23.
//

#ifndef BCC_ID_H
#define BCC_ID_H

#include <map>
#include "ast/ASTNode.h"

namespace bcc::AST::nodes {

    class ID : public ASTNode {
    private:
        std::string value;

        std::string generateSSAName(int idx);
    public:
        explicit ID(std::string value);

        void gen(term_vec_t & output, std::map<std::string, int> & varSSAMap, bool isLvalue) override;
    };

} // nodes

#endif //BCC_ID_H
