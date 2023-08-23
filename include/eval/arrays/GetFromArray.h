//
// Created by zhazha on 8/16/23.
//

#ifndef BCC_GETFROMARRAY_H
#define BCC_GETFROMARRAY_H

#include "../Term.h"

namespace bcc::arrays {

    class GetFromArray : public Term {
    private:
        tptr_t idx;
        tptr_t target;
    public:
        GetFromArray(tptr_t idx, tptr_t target);

    public:
        std::ostream & printToStream(std::ostream &out) const override;
    };

} // arrays

#endif //BCC_GETFROMARRAY_H
