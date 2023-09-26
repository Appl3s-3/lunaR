link_libraries(luna)

add_executable(triangle      ${CMAKE_CURRENT_SOURCE_DIR}/test_triangle.cpp)
add_executable(triangle_move ${CMAKE_CURRENT_SOURCE_DIR}/test_triangle_moving.cpp)
add_executable(bricker       ${CMAKE_CURRENT_SOURCE_DIR}/test_bricker.cpp)