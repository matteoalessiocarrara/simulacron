cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++11 -pipe -Wall -Wextra -Wshadow -pedantic)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -march=native -fomit-frame-pointer")
enable_testing()

add_executable(${PROJECT_NAME} main.cpp physics.cpp)
add_executable(t test.cpp physics.cpp)

target_link_libraries(${PROJECT_NAME} m SDL SDL_gfx)
target_link_libraries(t m SDL SDL_gfx)

add_test(t ${CMAKE_CURRENT_BINARY_DIR}/t)
