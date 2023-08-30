#ifndef BCC_ASSIGNMENT_H
#define BCC_ASSIGNMENT_H

#include <string>
#include "Term.h"

namespace bcc {

    class Assignment : public Term {
    private:
        tptr_t lhs;
        tptr_t rhs;
    public:
        Assignment(tptr_t lhs, tptr_t rhs);

        std::ostream & printToStream(std::ostream &out) const override;
    };

} // bcc

#endif //BCC_ASSIGNMENT_H
