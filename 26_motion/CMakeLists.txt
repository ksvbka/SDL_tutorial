cmake_minimum_required(VERSION 2.6)
project(pong)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")

file(COPY image DESTINATION .)

file(GLOB GAME_SOURCES "*.cpp" "*.h")

add_executable(pong ${GAME_SOURCES})

target_link_libraries(pong -lSDL2 -lSDL2_image)
