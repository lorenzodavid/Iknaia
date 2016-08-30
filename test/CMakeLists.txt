find_package(GTest REQUIRED)

add_executable(test_tracewinder test_tracewinder.cc)
target_link_libraries(test_tracewinder runtime_callers benchmark pthread ${GTEST_LIBRARIES})
add_test(test_tracewinder ${CMAKE_CURRENT_BINARY_DIR}/test_tracewinder)

add_executable(test_common test_common.cc)
target_link_libraries(test_common runtime_callers benchmark pthread ${GTEST_LIBRARIES})
add_test(test_common ${CMAKE_CURRENT_BINARY_DIR}/test_common)
