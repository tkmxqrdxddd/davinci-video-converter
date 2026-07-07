include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.6.0
)
FetchContent_MakeAvailable(Catch2)

# Ensure test input file exists
set(TEST_INPUT "${CMAKE_SOURCE_DIR}/tests/input.mp4")
if(NOT EXISTS "${TEST_INPUT}")
    file(WRITE "${TEST_INPUT}" "")
endif()

function(add_catch2_test name source)
    add_executable(${name} ${source} ${ARGN})
    target_include_directories(${name} PRIVATE "${CMAKE_SOURCE_DIR}/src/include")
    target_compile_definitions(${name} PRIVATE PROJECT_VERSION="${PROJECT_VERSION}")
    target_link_libraries(${name} PRIVATE Catch2::Catch2WithMain)
    add_test(NAME ${name} COMMAND ${name})
    set_tests_properties(${name} PROPERTIES WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endfunction()

add_catch2_test(test_parser test_parser.cpp ../src/parser.cpp)
add_catch2_test(test_validator test_validator.cpp ../src/validator.cpp)
add_catch2_test(test_converter test_converter.cpp ../src/converter.cpp)
