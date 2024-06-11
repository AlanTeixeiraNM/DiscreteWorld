cmake_minimum_required(VERSION 3.5.0)
project(PlanetsBind VERSION 1.0 LANGUAGES CXX)

#"Path" is the absolute path to /Lib/site-packages/pybind11/share/cmake
#in your instalation of pybind11 module
set(CMAKE_PREFIX_PATH "Path")

set(CMAKE_CXX_STANDARD 20)

find_package(pybind11 REQUIRED)

pybind11_add_module(Elite_planets 
	planetbind.cpp
	../../../c++/g++/planets_generator.cpp
	)
target_include_directories(Elite_planets PRIVATE ../../../c++/g++)