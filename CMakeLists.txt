if (WIN32)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
endif (WIN32)

if (UNIX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
endif (UNIX)

project(lines)

SET(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall")

file(GLOB SOURCES *.cpp *.c *.cc *.h *.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})
