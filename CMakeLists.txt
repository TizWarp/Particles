cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(ParticleSim)

add_subdirectory(./dependencies/)

file(GLOB_RECURSE PpopccornSrc CONFIGURE_DEPENDS ./ppopccorn_src/*.cpp)

add_executable(Ppopccorn ${PpopccornSrc})
target_include_directories(Ppopccorn PUBLIC ./dependencies/)

target_link_libraries(Ppopccorn PUBLIC ImGui-SFML::ImGui-SFML)
