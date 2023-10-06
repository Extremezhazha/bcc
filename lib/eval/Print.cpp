#include "../../include/eval/Print.h"

namespace bcc {
    std::ostream & Print::printToStream(std::ostream & out) const {
        return out << "std::cout << bc::utils::printer<" << *target << ">{} << std::endl;";
    }

    Print::Print(Term::tptr_t target) : target{std::move(target)} {}
} // bcc