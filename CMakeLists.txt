cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 14)

# Use ccache to speed up builds
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

project (aal)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem) 

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory (commander) 
include_directories ("${PROJECT_SOURCE_DIR}/commander")

add_executable (aal main.cpp)
target_link_libraries(aal commander ${Boost_LIBRARIES} )

# Unit tests (gtest based)
add_subdirectory (googletest) 
include_directories ("${PROJECT_SOURCE_DIR}/googletest/include")

FILE(GLOB test_sources tests/*.cpp )
add_executable (aal_test aal_test.cpp ${test_sources})

target_link_libraries(aal_test commander ${Boost_LIBRARIES} gtest)
add_dependencies(aal_test  commander)

# test runner invocation
add_custom_target(run_test COMMAND ./aal_test DEPENDS aal_test COMMENT "Run all unit tests")