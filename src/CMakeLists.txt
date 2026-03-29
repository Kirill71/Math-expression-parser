project(MathExpressionLib)
add_library(${PROJECT_NAME} STATIC)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if(ENABLE_COVERAGE)
    target_compile_options(${PROJECT_NAME} PUBLIC -O0 -g --coverage)
    target_link_options(${PROJECT_NAME} PUBLIC --coverage)
endif()

target_sources(${PROJECT_NAME}
    PRIVATE
        MathExpressionParser.cpp
        Definition.cpp
        Definition.h
        Expression.cpp
        Expression.h
        ExpressionErrorController.cpp
        ExpressionErrorController.h
        MathExpressionException.h
    PUBLIC
        FILE_SET HEADERS FILES
        MathExpressionParser.h
)