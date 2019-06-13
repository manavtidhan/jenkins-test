###################################
## package dependencies          ##
###################################

###########
## Build ##
###########

#############
## Headers ##
#############

include_directories(
  ${PROJECT_DIR}/tests/include
)

##########################
## Library dependencies ##
##########################

##########################
## Fixtures             ##
##########################

###########
## Tests ##
###########

## Queue test

set(TEST_NAME messaging_queue_test)
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/queue_test.cc)
set(TEST_LIB_DEP
  ${DEBUG_LIB_DEP}
  messaging_queue
  ${GOOGLETEST_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

## Manager test

set(TEST_NAME messaging_manager_test)
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/manager_test.cc)
set(TEST_LIB_DEP
  ${DEBUG_LIB_DEP}
  messaging_manager
  messaging_queue
  ${GOOGLETEST_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})