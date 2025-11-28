cmake_minimum_required(VERSION 3.10)
project(AlgoBot)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)

include_directories(include core/include engine/include)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

file(GLOB COMMON
  core/*.cpp
)

file(GLOB SOURCES
 src/*.cpp
)

file(GLOB ENGINE
 engine/*.cpp
)

add_executable(AlgoBot ${SOURCES} ${COMMON})

add_executable(Stocks ${ENGINE} ${COMMON})

target_compile_definitions(AlgoBot PRIVATE CHILD_PATH="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Stocks")
target_link_libraries(AlgoBot PRIVATE CURL::libcurl)
target_link_libraries(Stocks PRIVATE CURL::libcurl)
target_link_libraries(Stocks PUBLIC nlohmann_json::nlohmann_json)
