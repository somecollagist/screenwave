cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
	screenwave
	VERSION 0.1
	LANGUAGES CXX
)

add_executable(
	screenwave

	src/screenwave.hpp

	src/main.cpp
)

target_link_libraries(
	screenwave

	wayland-client
)