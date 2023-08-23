find_package(Boost COMPONENTS system program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(listener listener_main.cc)
target_link_libraries(listener PUBLIC frame Boost::program_options)
set_target_properties(listener PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(dbboot dbboot.cc)
target_link_libraries(dbboot PUBLIC frame Boost::program_options)
set_target_properties(dbboot PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)