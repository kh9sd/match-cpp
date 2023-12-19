cmake_minimum_required(VERSION 3.16)
project(match)

set(CMAKE_CXX_STANDARD 20)

# WARNING FLAGS
# warning flags are not global, bc they shouldn't be run on our external dependencies
#       if they are run, best case they cause a lot of noise that can obscure new warnings,
#       worse case compilation fails bc we error on warnings for some compilers

# create our warning flags for our three supported compilers, GCC, Clang, and MSVC
# you shouldn't need to use the private_*_WARNINGS_LIST vars directly, they are compiler 
# specific
string(JOIN ";" private_GCC_WARNINGS_LIST
                -Wall # general set of warnings
                -Wextra # extra warnings
                -Wcatch-value=2 # class types that are caught by value
                -Wfloat-equal # comparing floats directly for equality
                -Wundef # idk lol
                -Wcast-qual # removing type specifiers (ex. const) through casting
                -Wlogical-op # idk lol
                -Wmissing-declarations # for functions without a declaration
                -Wredundant-decls # if multiple declarations in same scope
                -Wshadow # if local var shadows another with the same name
                -Wsequence-point # weird unspecified order UB
                -Wno-psabi # gets rid of a really long warning in our external libraries
                # -Wpadded # warning about padding (might be useful for memory optimization later)
                # -march=native
                -Wpedantic # stricter warnings on non cross platform code
                -Werror # makes warnings errors, the final frontier
                )
string(JOIN ";" private_CLANG_WARNINGS_LIST
                -Wall# general set of warnings
                -Wextra # extra warnings
                -Wfloat-equal # comparing floats directly for equality
                -Wundef # Warn if an undefined identifier is evaluated in an #if directive. Such identifiers are replaced with zero.
                -Wcast-qual # removing type specifiers (ex. const) through casting
                -Wparentheses # controls -Wbitwise-conditional-parentheses, -Wbitwise-op-parentheses, -Wdangling-else, -Wlogical-not-parentheses, -Wlogical-op-parentheses, -Woverloaded-shift-op-parentheses, -Wparentheses-equality, -Wshift-op-parentheses.
                -Wmissing-declarations # for functions without a declaration
                -Wredundant-move # redundant move in return statement
                -Wshadow-all # if local var shadows another with the same name
                -Wunsequenced # weird unspecified order UB
                # -Wpadded # warning about padding (might be useful for memory optimization later)
                -Wpedantic # stricter warnings on non cross platform code
                -Wold-style-cast # warn on old C-style casts
                -Werror # makes warnings errors, the final frontier
                -Wpointer-arith # bad pointer arithmetic
                -Wpessimizing-move # bad moves
                -Wunused-variable # unused variable, either cast to void or use [[maybe_unused]]
                )
string(JOIN ";" private_MSVC_WARNINGS_LIST # msvc specifies warning levels, not individual flags
                /W4 # general warning set
                /permissive- # makes msvc warn about non-standard code
                /WX # makes warnings errors
                )

# warnings list to use, will apply correct set of flags depending on current compiler 
set(WARNINGS_LIST
        "$<$<CXX_COMPILER_ID:GNU>:${private_GCC_WARNINGS_LIST}>"
        "$<$<CXX_COMPILER_ID:Clang>:${private_CLANG_WARNINGS_LIST}>"
        "$<$<CXX_COMPILER_ID:MSVC>:${private_MSVC_WARNINGS_LIST}>")

add_compile_options("${WARNINGS_LIST}")

add_subdirectory(catch_tests)
add_executable(main main.cpp)
