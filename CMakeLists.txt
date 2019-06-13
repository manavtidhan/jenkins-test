###################################
## Project configuration         ##
###################################

set(MIN_CMAKE_VERSION 3.10)
cmake_minimum_required(VERSION ${MIN_CMAKE_VERSION})

set(SOUL_DIR ${CMAKE_CURRENT_SOURCE_DIR})

###################################
## Configuration options         ##
###################################

option(BUILD_TESTS "Build tests" ON)

###################################
## Build configuration           ##
###################################

# Compiler options
set (CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

set(PLUGIN_COMPILE_OPTIONS -fvisibility=hidden -fPIC)

# Debug flag to 'pierce the veil' of private
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Add debug flags
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_definitions(-DHR_DEBUG)

  # Enable libasan for buffer overflow checks in debug build.
  # You need to link asan as first library too.
  add_compile_options(-fsanitize=address)

  # Set the debug library variable.
  set(DEBUG_LIB_DEP asan)
endif()

# Add google test include paths

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest/googletest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest/googlemock/include)

###################################
## Testing                       ##
###################################

# Google Test libraries
set(GOOGLETEST_LIBRARIES gmock gmock_main)

if(BUILD_TESTS)
  enable_testing()
endif()

###################################
## Build third party             ##
###################################

add_subdirectory(third_party)

###################################
## Build components              ##
###################################

# Plugin system
add_subdirectory(plugins)

# Messaging system
add_subdirectory(messaging)

# Soul Sense (Perception system)
add_subdirectory(sense)

# Soul Knowledge (Knowledge system)
add_subdirectory(knowledge)