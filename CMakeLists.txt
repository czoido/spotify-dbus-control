cmake_minimum_required(VERSION 3.10.0)
project(SpotifyController)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(dbus-control main.cpp)
target_link_libraries(dbus-control CONAN_PKG::dbus-asio)