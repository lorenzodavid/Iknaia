include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable(bm_libunwind bm_libunwind.cc bm_common.cc)
target_link_libraries(bm_libunwind runtime_callers benchmark pthread)

add_executable(bm_backtrace bm_backtrace.cc bm_common.cc)
target_link_libraries(bm_backtrace runtime_callers benchmark pthread)

add_executable(bm_frameptr bm_frameptr.cc bm_common.cc)
target_link_libraries(bm_frameptr runtime_callers benchmark pthread)
set_target_properties(bm_frameptr PROPERTIES COMPILE_FLAGS "-fno-omit-frame-pointer")

add_executable(bm_tracewinder bm_tracewinder.cc bm_common.cc)
target_link_libraries(bm_tracewinder runtime_callers benchmark pthread)
