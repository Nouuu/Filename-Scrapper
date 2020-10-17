cmake_minimum_required(VERSION 3.16)
project(filename_scrapper C)

set(CMAKE_C_STANDARD 99)

add_executable(filename_scrapper main.c tools.c)