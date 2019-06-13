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

# Dummy plugin
set(LIB_NAME dummy_plugin)
set(LIB_DEP ${DEBUG_LIB_DEP} ${Boost_LIBRARIES})
file(GLOB SOURCE src/dummy_plugin.cc)

add_library(${LIB_NAME} SHARED ${SOURCE})
target_link_libraries(${LIB_NAME} ${LIB_DEP})
target_compile_options(${LIB_NAME} PRIVATE ${PLUGIN_COMPILE_OPTIONS})

###########
## Tests ##
###########

## Manager test

set(TEST_NAME plugin_manager_test)
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/manager_test.cc)
set(TEST_LIB_DEP ${DEBUG_LIB_DEP} ${GOOGLETEST_LIBRARIES} ${Boost_LIBRARIES} dl stdc++fs)

add_executable(${TEST_NAME} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_LIB_DEP})
add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

