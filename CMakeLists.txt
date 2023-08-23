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

set(D_GLIBCXX_USE_CXX11_ABI,"0")

# add current directory to include path
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_subdirectory(server)
add_subdirectory(client)
