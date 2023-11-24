cmake_minimum_required(VERSION 3.26)
project(infobez_lab2)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(LCG_FILES src/LCG.cpp)
set(SPECK_FILES src/Speck.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)


option(ENCODING "Build encoding executable" ON)
option(DECODING "Build decoding executable" ON)

if(ENCODING)
    add_executable(lcg_encode src/lcg_main.cpp ${LCG_FILES})
    add_executable(speck_encode src/speck_main.cpp ${SPECK_FILES})
    target_compile_definitions(lcg_encode PRIVATE ENCODING)
    target_compile_definitions(speck_encode PRIVATE ENCODING)
endif()

if(DECODING)
    add_executable(lcg_decode src/lcg_main.cpp ${LCG_FILES})
    add_executable(speck_decode src/speck_main.cpp ${SPECK_FILES})
    target_compile_definitions(lcg_decode PRIVATE DECODING)
    target_compile_definitions(speck_decode PRIVATE DECODING)
endif()


enable_testing()
add_executable(
        cipher_tests
        test/lcg_tests.cc
        test/speck_tests.cc
        ${LCG_FILES}
        ${SPECK_FILES}
)
target_link_libraries(
        cipher_tests
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(cipher_tests)