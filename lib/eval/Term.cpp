#include "../../include/eval/Term.h"

namespace bcc {
    std::ostream & operator<<(std::ostream & out, Term const & data) {
        return data.printToStream(out);
    }
}