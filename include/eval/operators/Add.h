#ifndef BCC_ADD_H
#define BCC_ADD_H

#include "../Term.h"

namespace bcc::operators {

        class Add : public Term {
        private:
            tptr_t lhs;
            tptr_t rhs;
        public:
            Add(tptr_t lhs, tptr_t rhs);
            std::ostream & printToStream(std::ostream &out) const override;
        };

    } // operators

#endif //BCC_ADD_H
