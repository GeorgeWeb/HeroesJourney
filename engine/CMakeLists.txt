cmake_minimum_required(VERSION 3.10)
# Require modern C++
# For Visual Studio
if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14")
endif(MSVC)
# For the other compilers (e.g. Clang, GCC..)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Engine)

#### Setup Directories ####
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)
add_library(engine STATIC ${SOURCES})

#### Add External Dependencies ####
# SFML
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# Build Dependencies
#add_executable(ENGINE ${SOURCES})
include_directories(ENGINE PRIVATE ${SFML_INCS})
link_libraries(ENGINE sfml-graphics)