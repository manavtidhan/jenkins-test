###################################
## project configuration         ##
###################################

cmake_minimum_required(VERSION ${MIN_CMAKE_VERSION})
project(soul_plugins)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

###################################
## build configuration           ##
###################################

###################################
## package dependencies          ##
###################################

find_package(Boost 1.65 REQUIRED COMPONENTS filesystem system)

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

#############
## Install ##
#############

#############
## Testing ##
#############

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()