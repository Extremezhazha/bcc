
#include "../../../include/eval/operators/Minus.h"

namespace bcc::operators {
    operators::Minus::Minus(tptr_t lhs, tptr_t rhs) : lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

    std::ostream & Minus::printToStream(std::ostream & out) const {
        return out << "bc::operators::minus<" << *lhs << ", " << *rhs << ">";
    }
} // operators