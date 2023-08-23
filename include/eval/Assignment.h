#ifndef BCC_ASSIGNMENT_H
#define BCC_ASSIGNMENT_H

#include <string>
#include "Term.h"

namespace bcc {

    class Assignment : public Term {
    private:
        std::string lhs;
        tptr_t rhs;
    public:
        Assignment(std::string lhs, tptr_t rhs);

        std::ostream & printToStream(std::ostream &out) const override;
    };

} // bcc

#endif //BCC_ASSIGNMENT_H
