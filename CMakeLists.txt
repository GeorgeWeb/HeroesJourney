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
# SFML
set(SFML_INCS "Engine/lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/Engine/lib/sfml/lib")

# ENGINE
add_subdirectory("Engine")
set(ENGINE_INCS ${CMAKE_SOURCE_DIR}/engine/src)
link_directories("${CMAKE_BINARY_DIR}/engine/src")

#### BUILD/EXECUTABLE Setup ####
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)
add_executable(HEROES ${SOURCES})
target_include_directories(HEROES PRIVATE ${SFML_INCS})
target_link_libraries(HEROES sfml-graphics)
target_include_directories(HEROES PUBLIC ${ENGINE_INCS})
target_link_libraries(HEROES engine)

set_target_properties(HEROES PROPERTIES 
	VS_DEBUGGER_WORKING_DIRECTORY
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

#### COPY RESOURCES VIA A CUSTOM TARGET
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
	-E copy_directory
	"${PROJECT_SOURCE_DIR}/res"
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res
)

add_dependencies(HEROES copy_resources)
add_dependencies(HEROES engine)

# END OF GAME BUILD SETUP