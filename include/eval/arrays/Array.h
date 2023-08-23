//
// Created by zhazha on 8/16/23.
//

#ifndef BCC_ARRAY_H
#define BCC_ARRAY_H

#include <vector>
#include "../Term.h"

namespace bcc::arrays {

    class Array : public Term {
    private:
        std::vector<tptr_t> contents;
    public:
        explicit Array(std::vector<tptr_t> contents);

    public:
        std::ostream & printToStream(std::ostream &out) const override;
    };
} // arrays

#endif //BCC_ARRAY_H
