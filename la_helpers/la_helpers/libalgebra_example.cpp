//
// Created by user on 20/10/22.
//

#include "la_helpers.h"

using namespace alghelp;

bool alghelp::LibalgebraExample::run_if_matches(const std::string& rname, unsigned int rwidth, unsigned int rdepth,
        const std::string& rctype)
{
    if (rname!=this->name()) {
        return false;
    }
    if (rwidth!=0 && rwidth!=this->width()) {
        return false;
    }
    if (rdepth!=0 && rdepth!=this->depth()) {
        return false;
    }
    if (!rctype.empty() && rctype==this->ctype()) {
        return false;
    }

    this->run();
    return true;
}
