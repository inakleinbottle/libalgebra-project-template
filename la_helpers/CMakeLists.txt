cmake_minimum_required(VERSION 3.20)

project(libalgebra_helpers VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

find_package(Boost COMPONENTS boost program_options)

add_library(la_helpers_library STATIC
        la_helpers/la_helpers.h
        la_helpers/libalgebra_examples_list.cpp
        la_helpers/libalgebra_example.cpp)

target_include_directories(la_helpers_library PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )
add_library(la_helpers::helpers ALIAS la_helpers_library)
target_link_libraries(la_helpers_library PUBLIC Libalgebra::Libalgebra)


add_library(la_helpers_main STATIC
        la_helpers/la_helper_main.cpp
        )
target_link_libraries(la_helpers_main
        PUBLIC la_helpers_library
        PRIVATE Boost::boost Boost::program_options)
add_library(la_helpers::main ALIAS la_helpers_main)
