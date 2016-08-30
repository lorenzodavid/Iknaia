include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_library(hashmap hashmap.c)
target_link_libraries(hashmap coumap pthread rt)

add_library(runtime_callers runtime_callers_libunwind.cc
			    runtime_callers_backtrace.cc
			    runtime_callers_frameptr.cc
			    runtime_callers_tracewinder.cc)
set_target_properties(runtime_callers PROPERTIES LINK_FLAGS " libunwind-ptrace.a libunwind.a libunwind-x86_64.a -fno-omit-frame-pointer")
target_link_libraries(runtime_callers libunwind-ptrace.a libunwind-x86_64.a libunwind.a hashmap)
