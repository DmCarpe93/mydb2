set(SRC_FILES ipc_connection.cc tcp_connection.cc)

#find_package(Boost COMPONENTS system REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

add_library(connection STATIC ${SRC_FILES})
target_link_libraries(connection ${Boost_Libraries})
