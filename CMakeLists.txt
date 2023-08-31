cmake_minimum_required(VERSION 3.11)
project(
    mydb2 
    VERSION 0.1 
    DESCRIPTION "MyDB2" 
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)   

find_package(Boost COMPONENTS system program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# add current directory to include path
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# include root directory to include path
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(common)
add_subdirectory(server)
add_subdirectory(client)
