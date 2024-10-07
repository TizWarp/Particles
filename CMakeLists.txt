cmake_minimum_required(VERSION 3.5.0)
project(ParticleSim)

find_package(SFML REQUIRED graphics window system)

file(GLOB_RECURSE ParticleSrc CONFIGURE_DEPENDS ./src/*.cpp)

add_executable(ParticleSim ${ParticleSrc})

target_link_libraries(ParticleSim sfml-window sfml-system sfml-graphics)
