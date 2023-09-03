set(SRC_FILES worker_thread.cc)

add_library(thread STATIC ${SRC_FILES})
target_link_libraries(thread task) 