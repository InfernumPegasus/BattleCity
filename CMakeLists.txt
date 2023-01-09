cmake_minimum_required(VERSION 3.23)
project(BattleCity)

set(CMAKE_CXX_STANDARD 23)

add_executable(BattleCity message/FieldMessage.cpp main.cpp
        message/FieldMessage.h message/FieldMessage.cpp
        message/FieldMessageSerializer.h message/FieldMessageSerializer.cpp)
