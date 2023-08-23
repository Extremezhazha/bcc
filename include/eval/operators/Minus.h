#ifndef BCC_MINUS_H
#define BCC_MINUS_H

#include "../Term.h"

namespace bcc::operators {

        class Minus : public Term {
        private:
            tptr_t lhs;
            tptr_t rhs;
        public:
            Minus(tptr_t lhs, tptr_t rhs);
            std::ostream & printToStream(std::ostream &out) const override;
        };

    } // operators

#endif //BCC_MINUS_H
