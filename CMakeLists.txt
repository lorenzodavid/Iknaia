cmake_minimum_required(VERSION 2.8)
project(unwind)
cmake_policy(VERSION 2.8.7)

INCLUDE(CMakeForceCompiler)
CMAKE_FORCE_C_COMPILER(gcc GNU)
CMAKE_FORCE_CXX_COMPILER(g++ GNU)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_definitions(-Werror)

enable_testing()

include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

# List of all subdirectories in the unwind project
#
list(APPEND UNWIND_SUBDIRS src test benchmark)

foreach(dir ${UNWIND_SUBDIRS})
  add_subdirectory(${dir})
  file(GLOB_RECURSE C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.c)
  file(GLOB_RECURSE CC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.cc)
  file(GLOB_RECURSE H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.h)
  list(APPEND CPPLINT_C_FILES ${C_FILES})
  list(APPEND CPPLINT_CC_FILES ${CC_FILES})
  list(APPEND CPPLINT_H_FILES ${H_FILES})
endforeach()
