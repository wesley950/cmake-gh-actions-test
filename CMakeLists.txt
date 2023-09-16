cmake_minimum_required(VERSION 3.25)
project(CmakeGHActionsTest)
add_executable(CmakeGHActionsTest main.cpp)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(CmakeGHActionsTest PRIVATE glfw)
