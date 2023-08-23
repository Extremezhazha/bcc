#ifndef BCC_RVALVARIABLE_H
#define BCC_RVALVARIABLE_H

#include <string>
#include "Term.h"

namespace bcc {

    class RvalVariable : public Term{
    private:
        std::string name;
    public:
        std::ostream & printToStream(std::ostream &out) const override;

        explicit RvalVariable(std::string name);
    };

} // bcc

#endif //BCC_RVALVARIABLE_H
