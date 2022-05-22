cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("Asteroids" LANGUAGES CXX)

# default compiler options and warnings
include(cmake/DefaultCompilerOptionsAndWarnings.cmake)

# static analyzers
include(cmake/StaticAnalyzers.cmake)

# sanitizers
include(cmake/Sanitizers.cmake)

include(FindOpenGL)

# Set project directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_GENERATOR_PLATFORM}/${CMAKE_BUILD_TYPE})

# Find necessary libs
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(OpenGL)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)

set(APP_NAME "AsteroidsApp")
add_executable(${APP_NAME} "")
add_subdirectory(src)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_EXTENSIONS OFF)
target_compile_features(${APP_NAME} PUBLIC cxx_std_20)
target_compile_options(${APP_NAME} PRIVATE ${SANITIZER_FLAGS} ${DEFAULT_COMPILER_OPTIONS_AND_WARNINGS})

target_include_directories(
    ${APP_NAME} PRIVATE
    "include"
)

if(WIN32 OR WIN64)
    target_link_libraries(
        ${APP_NAME} PRIVATE
        ${SANITIZER_FLAGS}
        ${SFML_LIBS}
        OpenGL::GLX
        )
else()
    target_link_libraries(
        ${APP_NAME} PRIVATE
        ${SANITIZER_FLAGS}
        ${SFML_LIBS}
        OpenGL::GLX
        )
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
   file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
   file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
    file(COPY ${CMAKE_SOURCE_DIR}/images DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
endif()
