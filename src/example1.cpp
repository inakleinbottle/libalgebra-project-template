

#include "la_helpers/la_helpers.h"

#include <iostream>


LIBALGEBRA_EXAMPLE(MyTestExample, 5, 5, DPReal) {
    TENSOR lhs(tensor_key(2));
    TENSOR rhs(tensor_key(1));

    lhs *= 2.0;
    auto result = lhs*rhs;

    SHOW(result);
}
