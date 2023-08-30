#include "../../../include/eval/operators/Divide.h"

namespace bcc::operators {
    operators::Divide::Divide(tptr_t lhs, tptr_t rhs) : lhs{std::move(lhs)}, rhs{std::move(rhs)} {}

    std::ostream & Divide::printToStream(std::ostream & out) const {
        return out << "bc::operators::divide<" << *lhs << ", " << *rhs << ">";
    }
} // operators