if (WIN32)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
endif (WIN32)

if (UNIX)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
endif (UNIX)

project(lines)

SET(CMAKE_CXX_FLAGS "-std=c++17 -g -Wall")

file(GLOB SOURCES src/*.cpp src/*.c src/*.cc src/*.h src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})
