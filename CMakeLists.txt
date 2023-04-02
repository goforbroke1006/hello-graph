cmake_minimum_required(VERSION 3.24)
project(hello-graph)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(examples/flight-ticket)

set(GTEST_VERSION 1.12.1)
if (NOT EXISTS ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION})
    message(STATUS "Building GTest")

    set(GTEST_ARCHIVE_FILENAME googletest-v${GTEST_VERSION}.zip)

    if (NOT EXISTS ${PROJECT_BINARY_DIR}/googletest-${GTEST_VERSION}.zip)
        file(DOWNLOAD https://github.com/google/googletest/archive/refs/tags/release-${GTEST_VERSION}.zip
                ${PROJECT_BINARY_DIR}/${GTEST_ARCHIVE_FILENAME})
    endif ()

    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xf ${GTEST_ARCHIVE_FILENAME}
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
    # -DCMAKE_BUILD_TYPE=Release
    execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION} -Dgtest_force_shared_crt=TRUE -DBUILD_GMOCK=FALSE
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION})
    execute_process(COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION})
endif ()

set(GTEST_INCLUDE_DIR ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION}/googletest/include)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(GTEST_LIBRARY ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION}/lib/libgtest.a)
    set(GTEST_MAIN_LIBRARY ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION}/lib/libgtest_main.a)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(GTEST_LIBRARY
            ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION}/lib/gtest.lib)
    set(GTEST_MAIN_LIBRARY
            ${PROJECT_BINARY_DIR}/googletest-release-${GTEST_VERSION}/lib/gtest_main.lib)
endif ()

enable_testing()

add_subdirectory(tests)
