cmake_minimum_required(VERSION 3.28)
project(MathExpressionParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-gdwarf-4")

option(BUILD_TESTING "Enable tests" ON)
option(ENABLE_COVERAGE "Enable coverage reporting" ON)
set(TEST_WORK_DIR ${CMAKE_BINARY_DIR} CACHE STRING "Working directory for tests" FORCE)

if (WIN32)
    MESSAGE(STATUS "Test coverage is not supported on the Windows platform")
    set(ENABLE_COVERAGE OFF)
endif()


add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE MathExpressionLib)

add_subdirectory(src)
if (BUILD_TESTING)
    message(STATUS "Testing is enabled")
    enable_testing()
    add_subdirectory(tests)
endif ()