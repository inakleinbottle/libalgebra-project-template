cmake_minimum_required(VERSION 3.20)

# Replace with your project name
project(LibalgebraProject VERSION 0.1)

# Bring libalgebra in to the project. It can be linked with the
# target Libalgebra::Libalgebra
add_subdirectory(extern/libalgebra)

# Now bring in the helpers library from la_helpers
add_subdirectory(la_helpers)


add_executable(libalgebra_project_demo src/example1.cpp)

target_link_libraries(libalgebra_project_demo PRIVATE
        la_helpers::main
    )
