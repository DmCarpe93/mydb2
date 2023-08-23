set(SRC_FILES listener_process.cc worker_process.cc)

add_library(process STATIC ${SRC_FILES})
#target_link_libraries(process ${Boost_Libraries})
target_link_libraries(process connection)