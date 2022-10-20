//
// Created by user on 20/10/22.
//

#include "la_helpers.h"

int main() {

    const auto& list = alghelp::get_example_list();

    for (const auto& example : list) {
        example->run();
    }

    return 0;
}
