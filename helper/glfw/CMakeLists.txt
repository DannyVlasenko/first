cmake_minimum_required(VERSION 3.14)

target_include_directories(first PRIVATE include)

target_sources(first PRIVATE
	glfw.cpp
)