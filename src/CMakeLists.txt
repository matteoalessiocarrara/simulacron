cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c11 -pipe -Wall -Wextra -Wshadow -pedantic)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -march=native -fomit-frame-pointer")

add_executable(${PROJECT_NAME} main.c physics.c)
add_executable(t test.c physics.c)

target_link_libraries(${PROJECT_NAME} m SDL SDL_gfx)
target_link_libraries(t m SDL SDL_gfx)
