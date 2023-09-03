add_subdirectory(connection)
add_subdirectory(message)

add_library(common INTERFACE)
target_link_libraries(common INTERFACE connection message ${Boost_Libraries})