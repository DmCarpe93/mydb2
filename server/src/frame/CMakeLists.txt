add_subdirectory(process)

add_library(frame INTERFACE)
target_link_libraries(frame INTERFACE process)
