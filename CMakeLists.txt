cmake_minimum_required(VERSION 3.12)
project(b64 C)

set(CMAKE_C_STANDARD 11)

add_executable(b64 main.c base64.h base64.c definitions.h)