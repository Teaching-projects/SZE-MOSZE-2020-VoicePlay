cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_COMPILER "gcc-10")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")

project("Unittest")
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# locate unit.cpp


# Link runTests with what we want to test 
# and the GTest and pthread library
add_executable(runTests unittest.cpp ../unit.cpp ../Hero.cpp ../JSON.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
