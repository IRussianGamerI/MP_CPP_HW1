set(TEST_SOURCES unit/tests.cpp)
add_executable(tests ${TEST_SOURCES})
target_include_directories(tests PUBLIC ${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tests gtest gtest_main)
