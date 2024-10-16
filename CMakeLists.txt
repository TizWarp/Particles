cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(ParticleSim)

add_subdirectory(./dependencies/)

file(GLOB_RECURSE SimSrc CONFIGURE_DEPENDS ./src/*.cpp)

add_executable(ParticleSim ${SimSrc})
target_include_directories(ParticleSim PUBLIC ./dependencies/)

target_link_libraries(ParticleSim PUBLIC ImGui-SFML::ImGui-SFML)
