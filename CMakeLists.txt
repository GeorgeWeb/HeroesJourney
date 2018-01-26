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

project(Heroes_Journey)

#### Setup Directories ####
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### BUILD/EXECUTABLE Setup ####
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)
add_executable(SRC ${SOURCES})
target_include_directories(SRC PRIVATE ${SFML_INCS})
target_link_libraries(SRC sfml-graphics)

set_target_properties(SRC PROPERTIES 
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

#### COPY RESOURCES VIA A CUSTOM TARGET
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
	-E copy_directory
	"${PROJECT_SOURCE_DIR}/res"
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

add_dependencies(SRC copy_resources)