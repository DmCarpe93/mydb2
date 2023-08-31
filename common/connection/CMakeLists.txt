set(SRC_FILES ipc_connection.cc tcp_connection.cc)

add_library(connection STATIC ${SRC_FILES})
target_link_libraries(connection ${Boost_Libraries})
