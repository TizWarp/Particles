cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(ParticleSim)

find_package(SFML REQUIRED graphics window system)

file(GLOB_RECURSE PpopccornSrc CONFIGURE_DEPENDS ./ppopccorn_src/*.cpp)

add_library(Ppopccorn SHARED ${PpopccornSrc})

target_link_libraries(Ppopccorn sfml-window sfml-system sfml-graphics)

file(GLOB SimulationsGlob LIST_DIRECTORIES true ./simulations/*)

set(SimulationDirs)

foreach(dir ${SimulationsGlob})
  if(IS_DIRECTORY ${dir})
    list(APPEND SimulationDirs ${dir})
  else()
    continue()
  endif()
endforeach()

set(ProjectIDs)

foreach(dir ${SimulationDirs})
  get_filename_component(ProjectName ${dir} NAME)
  file(GLOB_RECURSE ProjectSrc CONFIGURE_DEPENDS ${dir}/*.cpp)
  add_executable(${ProjectName} ${ProjectSrc})
  target_link_libraries(${ProjectName} PUBLIC Ppopccorn)
  target_include_directories(${ProjectName} PUBLIC ./ppopccorn_src/)
endforeach()
