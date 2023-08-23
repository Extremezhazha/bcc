//
// Created by zhazha on 8/16/23.
//

#include "../../../include/eval/arrays/GetFromArray.h"

namespace bcc::arrays {
    std::ostream & GetFromArray::printToStream(std::ostream & out) const {
        return out << "bc::arrays::get<" << *idx << "::value, " << *target << ">";
    }

    GetFromArray::GetFromArray(Term::tptr_t idx, Term::tptr_t target) : idx{std::move(idx)}, target{std::move(target)} {}
} // arrays