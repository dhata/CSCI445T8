cmake_minimum_required(VERSION 2.8)
project(CenterFinder)
SET(COMPILE_DEFINITION -Werror)
add_executable(CenterFinder centerfinder.cpp)
target_link_libraries(CenterFinder wiringPi)

