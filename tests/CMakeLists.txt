project(hello-graph-tests)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${gtest_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp graph_source.cpp path.cpp)
add_test(AllTests ${PROJECT_NAME})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
endif ()