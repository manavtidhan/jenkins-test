###################################
## Project configuration         ##
###################################

cmake_minimum_required(VERSION ${MIN_CMAKE_VERSION})
project(soul_sense)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

###################################
## build configuration           ##
###################################

###################################
## package dependencies          ##
###################################

find_package(Boost 1.65 REQUIRED COMPONENTS filesystem system program_options)
find_package(OpenCV 4.0.1 REQUIRED)

###################################
## third party cmake             ##
###################################

###########
## Build ##
###########

## Headers
include_directories(
  include
  ${SOUL_DIR}/plugins/include
  ${SOUL_DIR}/messaging/include
  ${SOUL_DIR}/knowledge/include
  ${Boost_INCLUDE_DIRS}
)

# Soul sense manager
set(EXE_NAME soul_sense_manager)
set(LIB_DEP
  ${DEBUG_LIB_DEP}
  messaging_manager
  messaging_queue
  ${Boost_LIBRARIES}
  dl
  stdc++fs
)

set(SOURCE
  src/hw_manager.cc
  src/manager.cc
  src/manager_main.cc
)

add_executable(${EXE_NAME} ${SOURCE})
target_link_libraries(${EXE_NAME} ${LIB_DEP})

#############
## Install ##
#############

#############
## Testing ##
#############

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()