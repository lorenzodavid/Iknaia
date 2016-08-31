find_package(GTest REQUIRED)

add_library(test_common test_common.cc)

add_executable(test_runtime_callers test_runtime_callers.cc)
target_link_libraries(test_runtime_callers test_common runtime_callers benchmark pthread ${GTEST_LIBRARIES})
add_test(test_runtime_callers ${CMAKE_CURRENT_BINARY_DIR}/test_runtime_callers)
