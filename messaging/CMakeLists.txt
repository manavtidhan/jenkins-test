###################################
## project configuration         ##
###################################

cmake_minimum_required(VERSION ${MIN_CMAKE_VERSION})
project(soul_messaging)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

###################################
## build configuration           ##
###################################

###################################
## package dependencies          ##
###################################

###################################
## third party cmake             ##
###################################

###########
## Build ##
###########

## Headers
include_directories(
  include
  ${Boost_INCLUDE_DIRS}
)

## Messaging queue

set(TARGET_OUTPUT messaging_queue)
set(TARGET_SOURCE ${PROJECT_DIR}/src/queue.cc)
set(TARGET_LIB_DEP ${DEBUG_LIB_DEP})
add_library(${TARGET_OUTPUT} SHARED ${TARGET_SOURCE})
target_link_libraries(${TARGET_OUTPUT} ${TARGET_LIB_DEP})

## Messaging manager

set(TARGET_OUTPUT messaging_manager)
set(TARGET_SOURCE ${PROJECT_DIR}/src/manager.cc)
set(TARGET_LIB_DEP ${DEBUG_LIB_DEP} messaging_queue)
add_library(${TARGET_OUTPUT} SHARED ${TARGET_SOURCE})
target_link_libraries(${TARGET_OUTPUT} ${LIB_DEP})

#############
## Install ##
#############

#############
## Testing ##
#############

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()