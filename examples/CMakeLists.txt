add_executable(simple_named_parameter simple_named_parameter.cpp)
#target_include_directories(simple_named_parameter PRIVATE ${CMAKE_CURRENT_LIST_DIR}/..)
target_link_libraries(simple_named_parameter cpp-pre::named_param)