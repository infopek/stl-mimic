cmake_minimum_required(VERSION 3.16..3.24)

project(Core	
    VERSION 1.0.0
    DESCRIPTION "Data structure implementations"
    LANGUAGES CXX)  

add_library(Core 
    src/vector.cpp)
add_library(Core::Core ALIAS Core)

target_include_directories(
    Core 
		PUBLIC 	
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)

