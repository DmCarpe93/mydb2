
find_package(Protobuf REQUIRED)

# Generate the protobuf sources
protobuf_generate_cpp(PROTO_MESSAGE_SRCS PROTO_MESSAGE_HDRS message.proto)

add_library(message STATIC ${PROTO_MESSAGE_SRCS})
target_link_libraries(message ${Protobuf_LIBRARIES})
