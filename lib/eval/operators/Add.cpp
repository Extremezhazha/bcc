#include "../../../include/eval/operators/Add.h"

namespace bcc::operators {
    std::ostream & Add::printToStream(std::ostream & out) const {
        return out << "bc::operators::add<" << *lhs << ", " << *rhs << ">";
    }

    Add::Add(tptr_t lhs, tptr_t rhs) : lhs{std::move(lhs)}, rhs{std::move(rhs)} {}
} // operators