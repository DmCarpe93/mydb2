find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(connection)
add_subdirectory(process)

add_library(frame INTERFACE)
target_link_libraries(frame INTERFACE process connection ${Boost_Libraries})