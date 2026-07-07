cmake_minimum_required(VERSION 3.20)
project(davinci-video-converter VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Main executable ---
add_executable(davinci-video-converter
    src/main.cpp
    src/parser.cpp
    src/validator.cpp
    src/converter.cpp
)
target_include_directories(davinci-video-converter PRIVATE src/include)
target_compile_definitions(davinci-video-converter PRIVATE PROJECT_VERSION="${PROJECT_VERSION}")

# --- Install ---
install(TARGETS davinci-video-converter RUNTIME DESTINATION bin)

# --- Tests ---
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    include(CTest)
    add_subdirectory(tests)
endif()
