#ifndef BCC_TERM_H
#define BCC_TERM_H

#include <string>
#include <iostream>
#include <memory>

namespace bcc {
    class Term {
    protected:
        virtual std::ostream & printToStream(std::ostream & out) const = 0;
        using tptr_t = std::unique_ptr<Term>;
    public:
        friend std::ostream & operator<<(std::ostream & out, Term const & data);
        virtual ~Term() = default;
    };
}

#endif //BCC_TERM_H
