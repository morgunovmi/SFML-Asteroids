cmake_minimum_required(VERSION 3.13)

project(Asteroids VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} "")
add_subdirectory(src)

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SFML_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE "include")
