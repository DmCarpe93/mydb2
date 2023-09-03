include_directories(${CMAKE_BINARY_DIR})

set(SRC_FILES listener_process.cc worker_process.cc)

add_library(process STATIC ${SRC_FILES})
target_link_libraries(process PUBLIC thread task message connection) 