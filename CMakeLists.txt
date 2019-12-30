cmake_minimum_required(VERSION 3.14)

project(first VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

list(APPEND CMAKE_PREFIX_PATH ${GLEW_LOCATION})

set(GLEW_USE_STATIC_LIBS TRUE)
add_compile_definitions(GLEW_STATIC)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(first first.cpp)
target_link_libraries(first PRIVATE glfw GLEW::glew_s OpenGL::GL)

add_subdirectory(helper)
add_subdirectory(shaders)