#include "../../include/eval/Print.h"

namespace bcc {
    std::ostream & Print::printToStream(std::ostream & out) const {
        return out << "std::cout << " << *target << "::value << std::endl;";
    }

    Print::Print(Term::tptr_t target) : target{std::move(target)} {}
} // bcc