//
// Created by user on 20/10/22.
//

#include "la_helpers.h"

#include <vector>

using namespace alghelp;


std::vector<std::unique_ptr<LibalgebraExample>>& alghelp::get_example_list() noexcept
{
    static std::vector<std::unique_ptr<LibalgebraExample>> examples;
    return examples;
}
