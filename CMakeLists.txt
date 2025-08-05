cmake_minimum_required(VERSION 3.10)
project(Vcpkg)

find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(demo)