//
// Created by zhazha on 8/16/23.
//

#include "../../../include/eval/arrays/Array.h"

namespace bcc::arrays {
    std::ostream & Array::printToStream(std::ostream & out) const {
        out << "bc::arrays::type_pack<";
        auto it = contents.begin();
        if (it != contents.end()) {
            out << **it;
            ++it;
            for (; it != contents.end(); ++it)
                out << ", " << **it;
        }
        return out << ">";
    }

    Array::Array(std::vector<tptr_t> contents) : contents{std::move(contents)} {}
} // arrays