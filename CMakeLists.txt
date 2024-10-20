cmake_minimum_required(VERSION 3.5.0)
project(AparatusVivi)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

find_package(spdlog REQUIRED)

file(GLOB_RECURSE Src CONFIGURE_DEPENDS ./src/*.cpp)
add_executable(AparatusVivi ${Src})

target_link_libraries(AparatusVivi PUBLIC OpenGL::GL)
target_link_libraries(AparatusVivi PUBLIC OpenGL::GLU)
target_link_libraries(AparatusVivi PUBLIC GLEW::GLEW)
target_link_libraries(AparatusVivi PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(AparatusVivi PUBLIC spdlog::spdlog_header_only)

target_include_directories(AparatusVivi PUBLIC ./includes/)
