#include <utility>

#include "../../include/eval/RvalVariable.h"

namespace bcc {
    std::ostream & RvalVariable::printToStream(std::ostream & out) const {
        return out << name;
    }

    RvalVariable::RvalVariable(std::string name) : name{std::move(name)} {}
} // bcc