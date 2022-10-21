//
// Created by user on 20/10/22.
//

#include "la_helpers.h"


#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, const char** argv) {
    unsigned width;
    unsigned depth;

    po::options_description descr("Options");
    descr.add_options()
            ("help", "Display the help message and quit")
            ("width", po::value<unsigned>(&width)->default_value(0), "Set a width filter for examples")
            ("depth", po::value<unsigned>(&depth)->default_value(0), "Set a depth filter for examples")
            ("name", po::value<std::string>()->default_value(""), "Set a name filter for examples")
            ("ctype", po::value<std::string>()->default_value(""), "Set a ctype filter for examples")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, descr), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << descr << '\n';
        return EXIT_SUCCESS;
    }

    const auto& list = alghelp::get_example_list();

    for (const auto& example : list) {
        try {
            example->run();
        } catch (std::exception& exc) {
            std::cerr << exc.what() << '\n';
        }
    }

    return EXIT_SUCCESS;
}
