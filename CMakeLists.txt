cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(code
        src/BlockList.cpp
        src/Book.cpp
        src/Account.cpp
        src/main.cpp
)