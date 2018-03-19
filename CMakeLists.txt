cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER gcc-7)
set(CMAKE_CXX_COMPILER g++-7)

file(GLOB_RECURSE srcs ./src/*.cpp)

add_compile_options(--std=c++17)

add_executable(main ${srcs})

target_link_libraries(main glfw GL X11 pthread Xrandr Xi dl)
