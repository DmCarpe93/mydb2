include_directories(${CMAKE_BINARY_DIR})

set(SRC_FILES task_builder.cc worker_task.cc)

add_library(task STATIC ${SRC_FILES})
target_link_libraries(task message connection) 