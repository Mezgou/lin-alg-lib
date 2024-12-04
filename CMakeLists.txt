cmake_minimum_required(VERSION 3.29)
project(lin-alg-lib)

add_compile_options(-Wno-error)

add_subdirectory(cunit/CUnit)

include_directories(cunit/CUnit)

add_executable(lin-alg-lib 
    src/main.cpp
    src/matrix/matrix.cpp
    src/matrix/test_matrix.cpp
)

target_link_libraries(lin-alg-lib PRIVATE cunit)