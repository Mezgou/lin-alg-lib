cmake_minimum_required(VERSION 3.29)
project(lin-alg-lib)

include_directories(/usr/include/CUnit)

link_libraries(/usr/lib/libcunit.so)

include_directories()

add_executable(lin-alg-lib 
    src/main.cpp
)

target_link_libraries(lin-alg-lib PRIVATE cunit)