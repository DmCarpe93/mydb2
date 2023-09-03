add_subdirectory(task)
add_subdirectory(thread)
add_subdirectory(process)

add_library(frame INTERFACE)
target_link_libraries(frame INTERFACE process task thread)
