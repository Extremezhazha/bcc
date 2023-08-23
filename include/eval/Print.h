#ifndef BCC_PRINT_H
#define BCC_PRINT_H

#include <memory>
#include "Term.h"

namespace bcc {
    class Print : public Term {
    public:
        explicit Print(tptr_t target);

    private:
        tptr_t target;
    public:
        std::ostream & printToStream(std::ostream &out) const override;
    };
} // bcc

#endif //BCC_PRINT_H
