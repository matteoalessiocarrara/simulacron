cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11 -pipe -Wall -Wextra -Wshadow -pedantic)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -march=native -fomit-frame-pointer")

add_executable(${PROJECT_NAME} main.cpp physics.cpp)
target_link_libraries(${PROJECT_NAME}  SDL SDL_gfx)
