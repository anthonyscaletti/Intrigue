cmake_minimum_required(VERSION 3.5.1)
project (Intrigue)

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

add_executable(Intrigue main.cpp encrypt.cpp decrypt.cpp encrypt.h decrypt.h)

link_directories(/usr/include/)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
