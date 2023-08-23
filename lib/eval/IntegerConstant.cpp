#include <iostream>
#include "../../include/eval/IntegerConstant.h"


std::ostream & bcc::IntegerConstant::printToStream(std::ostream & out) const {
    return out << "bc::integer_constant<" << val << ">";
}

bcc::IntegerConstant::IntegerConstant(int val) : val{val} {}
