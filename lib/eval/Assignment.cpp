#include "../../include/eval/Assignment.h"

namespace bcc {
    std::ostream & Assignment::printToStream(std::ostream & out) const {
        return out << "using " << *lhs << " = " << *rhs << ";";
    }

    Assignment::Assignment(Term::tptr_t lhs, Term::tptr_t rhs) : lhs{std::move(lhs)}, rhs{std::move(rhs)} {}
} // bcc