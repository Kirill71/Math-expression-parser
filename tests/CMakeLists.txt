project(MathExpressionTests)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE tests.cpp)

# test, lib, exe in one place
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(${PROJECT_NAME} PRIVATE
        MathExpressionLib
        GTest::gtest_main
)

if(ENABLE_COVERAGE)
    add_custom_target(coverage
            COMMAND ctest --output-on-failure
            COMMAND lcov --capture
            --rc geninfo_unexecuted_blocks=1
            --ignore-errors gcov
            --ignore-errors mismatch
            --directory ${CMAKE_BINARY_DIR}
            --output-file coverage.info
            COMMAND lcov --remove coverage.info '/usr/*' '*/_deps/*'
            --ignore-errors unused
            --output-file coverage.info
            COMMAND genhtml coverage.info --output-directory coverage_report
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

include(GoogleTest)

if (WIN32 AND MSVC)
    #MSVC supports multi-conf generator so we need to specify conf. type. trick for Github CI
    set(TEST_WORK_DIR ${TEST_WORK_DIR}/bin/${CMAKE_BUILD_TYPE})
else()
    set(TEST_WORK_DIR ${TEST_WORK_DIR}/bin)
endif()

# specify work dir directly in order to find test files.
gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${TEST_WORK_DIR})