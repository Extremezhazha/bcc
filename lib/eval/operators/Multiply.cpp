#include "../../../include/eval/operators/Multiply.h"

namespace bcc::operators {
    operators::Multiply::Multiply(tptr_t lhs, tptr_t rhs) : lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

    std::ostream & Multiply::printToStream(std::ostream & out) const {
        return out << "bc::operators::multiply<" << *lhs << ", " << *rhs << ">";
    }
} // operators