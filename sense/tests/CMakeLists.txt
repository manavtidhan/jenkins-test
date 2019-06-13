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

# Dummy sense plugin

set(LIB_NAME dummy_sense_plugin)
set(LIB_DEP ${DEBUG_LIB_DEP} ${Boost_LIBRARIES})
file(GLOB SOURCE src/dummy_sense_plugin.cc)

add_library(${LIB_NAME} SHARED ${SOURCE})
target_link_libraries(${LIB_NAME} ${LIB_DEP})
target_compile_options(${LIB_NAME} PRIVATE ${PLUGIN_COMPILE_OPTIONS})

# Dummy sense hardware plugin

set(LIB_NAME dummy_sense_hw_plugin)
set(LIB_DEP ${DEBUG_LIB_DEP} ${Boost_LIBRARIES})
file(GLOB SOURCE src/dummy_sense_hw_plugin.cc)

add_library(${LIB_NAME} SHARED ${SOURCE})
target_link_libraries(${LIB_NAME} ${LIB_DEP})
target_compile_options(${LIB_NAME} PRIVATE ${PLUGIN_COMPILE_OPTIONS})

###########
## Tests ##
###########

## Plugin manager test

set(TEST_NAME sense_plugin_manager_test)
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/plugin_manager_test.cc)
set(TEST_LIB_DEP ${DEBUG_LIB_DEP} ${GOOGLETEST_LIBRARIES} ${Boost_LIBRARIES} dl stdc++fs)

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

## Math interfaces test

set(TEST_NAME sense_math_test)
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/sense_math_test.cc)
set(TEST_LIB_DEP ${DEBUG_LIB_DEP} ${GOOGLETEST_LIBRARIES})

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

## Sense msgs interfaces test

set(TEST_NAME sense_msgs_test)
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/sense_msgs_test.cc)
set(TEST_LIB_DEP ${DEBUG_LIB_DEP} ${GOOGLETEST_LIBRARIES} ${OpenCV_LIBS})

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

## Soul sense manager test

set(TEST_NAME sense_manager_test)
set(SOURCE
  ${PROJECT_DIR}/src/manager.cc
  ${PROJECT_DIR}/src/hw_manager.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/manager_test.cc
)
set(TEST_LIB_DEP
  ${DEBUG_LIB_DEP}
  ${GOOGLETEST_LIBRARIES}
  ${Boost_LIBRARIES}
  messaging_manager
  messaging_queue
  dl
  stdc++fs
)

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/sense/tests)


## Soul sense manager messaging isolation test

set(TEST_NAME sense_manager_msg_test)
set(SOURCE
  ${PROJECT_DIR}/src/manager.cc
  ${PROJECT_DIR}/src/hw_manager.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/manager_msgs_test.cc
)
set(TEST_LIB_DEP
  ${DEBUG_LIB_DEP}
  ${GOOGLETEST_LIBRARIES}
  ${Boost_LIBRARIES}
  messaging_manager
  messaging_queue
  dl
  stdc++fs
)

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/sense/tests)

## Soul sense hardware manager test

set(TEST_NAME sense_hw_manager_test)
set(SOURCE
  ${PROJECT_DIR}/src/hw_manager.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/hw_manager_test.cc
)
set(TEST_LIB_DEP
  ${DEBUG_LIB_DEP}
  ${GOOGLETEST_LIBRARIES}
  ${Boost_LIBRARIES}
  messaging_manager
  messaging_queue
  dl
  stdc++fs
)

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/sense/tests)