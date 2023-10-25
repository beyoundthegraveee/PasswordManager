cmake_minimum_required(VERSION 3.24)
project(s24911)

set(CMAKE_CXX_STANDARD 20)

add_executable(s24911 main.cpp Encryption.cpp Encryption.h File.cpp File.h Options.cpp Options.h)
