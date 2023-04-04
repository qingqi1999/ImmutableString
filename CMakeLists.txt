cmake_minimum_required(VERSION 3.0.0)
project(ds_string VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

add_executable(ds_string_test main.cpp ds_string_test.cpp immutable_string.h immutable_string.cpp immutable_string_pool.h)
enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(ds_string_test PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(AllTestsInMain main)

find_package(TBB CONFIG REQUIRED)
target_link_libraries(ds_string_test PRIVATE TBB::tbb TBB::tbbmalloc)

find_package(glog CONFIG REQUIRED)
target_link_libraries(ds_string_test PRIVATE glog::glog)