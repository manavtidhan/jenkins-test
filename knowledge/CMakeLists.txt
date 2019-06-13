###################################
## Project configuration         ##
###################################

cmake_minimum_required(VERSION ${MIN_CMAKE_VERSION})
project(soul_knowledge)
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
  ${SOUL_DIR}/sense/include
  ${Boost_INCLUDE_DIRS}
)

#############
## Install ##
#############

#############
## Testing ##
#############

