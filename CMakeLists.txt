cmake_minimum_required(VERSION 3.14)

project(Asteroids VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} "")
add_subdirectory(src)

find_package(SFML 2 REQUIRED COMPONENTS graphics system window)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SFML_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE "include")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
