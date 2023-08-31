include_directories(${CMAKE_BINARY_DIR})

find_package(Protobuf REQUIRED)

add_executable(dbsql dbsql.cc)
target_link_libraries(dbsql connection message)

set_target_properties(dbsql PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
