#ifndef BCC_MULTIPLY_H
#define BCC_MULTIPLY_H

#include "../Term.h"

namespace bcc::operators {

        class Multiply : public Term {
        private:
            tptr_t lhs;
            tptr_t rhs;
        public:
            Multiply(tptr_t lhs, tptr_t rhs);
            std::ostream & printToStream(std::ostream &out) const override;
        };

    } // operators

#endif //BCC_MULTIPLY_H
