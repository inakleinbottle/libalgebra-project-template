cmake_minimum_required(VERSION 3.20)

# Replace with your project name
project(LibalgebraProject VERSION 0.1)

# Bring libalgebra in to the project. It can be linked with the
# target Libalgebra::Libalgebra
add_subdirectory(extern/libalgebra)

include(GNUInstallDirs)

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
target_link_libraries(la_helpers_main PUBLIC la_helpers_library)
add_library(la_helpers::main ALIAS la_helpers_main)


add_executable(libalgebra_project_demo src/example1.cpp)

target_link_libraries(libalgebra_project_demo PRIVATE
        la_helpers::main
    )
