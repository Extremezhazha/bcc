#ifndef BCC_INTEGERCONSTANT_H
#define BCC_INTEGERCONSTANT_H

#include "Term.h"

namespace bcc {
    class IntegerConstant : public Term {
    private:
        int val;
    public:
        explicit IntegerConstant(int val);

        std::ostream & printToStream(std::ostream &out) const override;
    };
}


#endif //BCC_INTEGERCONSTANT_H
