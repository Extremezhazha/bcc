#ifndef BCC_DIVIDE_H
#define BCC_DIVIDE_H

#include "../Term.h"

namespace bcc::operators {

        class Divide : public Term {
        private:
            tptr_t lhs;
            tptr_t rhs;
        public:
            Divide(tptr_t lhs, tptr_t rhs);
            std::ostream & printToStream(std::ostream &out) const override;
        };

    } // operators

#endif //BCC_DIVIDE_H
