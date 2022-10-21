# Libalgebra project template
This is an template for experimental code based on Libalgebra.
Libalgebra is included as a submodule, so you will need to make sure to include `--recurse-submodules` when cloning this repo.
Also included is a helper library which provides a fixture-like tool for writing code based on a specific Libalgebra environment.
To access this, use the `LIBALGEBRA_EXAMPLE` macro, which will construct the required environment in which the code that follows can run.
This fixture is based on the `alg_types` fixture found in Libalgebra.
Here is a simple example of how it can be used:
```c++
#include <la_helpers/la_helpers.h>

LIBALGEBRA_EXAMPLE(2, 2, DPReal) {
    LIE x(LET(1), 1.0);
    
    auto y = exp(maps.l2t(x));
    
    SHOW(y);
}
```
The arguments for the macro are the width, maximum degree, and coefficient type (choice of `SPReal`, `DPReal`, and `Rational`).
The `SHOW` macro, also provided in the `la_helpers` header, prints the name of the variable followed by the value.

The `CMakeLists.txt` includes everything you need to get started.
It brings in Libalgebra from the submodule (cloned into extern/libalgebra) and also the helpers (found in la_helpers).
You can create executable targets for any set of examples, constructed as above, from any number of `cpp` files.
This should link the target `la_helpers::library`, or `la_halpers::main` which also provides a `main` function which runs all registered examples (this is highly recommended).
There is an example target set up in the repository that you can use as an example.

## Building
To build your examples, you should use the CMake command line interface, or your CMake-aware IDE.
The commands you will need are as follows: (from the repo root directory)
```
cmake -GNinja -B build_dir -S .
cmake --build build_dir
```
You can remove or change the `-GNinja` flag to change the build system but Ninja is a good option if you have it installed.
The `build_dir` option sets the place where the build files and ultimately the built targets will be placed.
After compiling, you will be able to find your compiled executables inside `build_dir`, with the same name that appears inside the `CMakeLists.txt`.
In the sample target in the template, you can run this using
```
build_dir/libalgebra_project_demo
```
