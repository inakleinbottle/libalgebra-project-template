

#include "la_helpers/la_helpers.h"

#include <iostream>


LIBALGEBRA_EXAMPLE(MyTestExample, 5, 5, DPReal) {
    typename TENSOR::KEY lkey(LET(2));
    TENSOR lhs(lkey);
    typename TENSOR::KEY rkey(LET(1));
    TENSOR rhs(rkey);

    lhs *= 2.0;
    auto result = lhs*rhs;

    std::cout << result << '\n';
}
