cmake_minimum_required(VERSION 3.23)
project(BattleCity)

set(CMAKE_CXX_STANDARD 23)

#Folders required for tests
add_subdirectory(tests/lib/googletest)
include_directories(tests/lib/googletest/googletest/include)

#Main project files
add_executable(BattleCity
        main.cpp)

#Tests
add_executable(Tests
        message/FieldMessage.cpp
        message/FieldMessageSerializer.cpp
        tests/FieldMessageFixture.cpp)

#Link with GTests 'main' function
target_link_libraries(Tests gtest gtest_main)