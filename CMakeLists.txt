cmake_minimum_required(VERSION 3.6)
project(tools_to_remember)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(googletest)

include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

add_subdirectory(old)

# all tests
set(ALL_TESTS
        bubble_sort.cpp
        bucket_sort.cpp
        counting_sort.cpp
        heapsort.cpp
        insertion_sort.cpp
        mergesort.cpp
        quicksort.cpp
        radix_sort.cpp
        selection_sort.cpp
        shellsort.cpp)

add_executable(test_all test_all.cpp ${ALL_TESTS})
target_link_libraries(test_all gtest gmock)

# sorting
add_executable(selection_sort selection_sort.cpp)
target_link_libraries(selection_sort gtest gmock gtest_main)

add_executable(insertion_sort insertion_sort.cpp)
target_link_libraries(insertion_sort gtest gmock gtest_main)

add_executable(bubble_sort bubble_sort.cpp)
target_link_libraries(bubble_sort gtest gmock gtest_main)

add_executable(shellsort shellsort.cpp)
target_link_libraries(shellsort gtest gmock gtest_main)

add_executable(mergesort mergesort.cpp)
target_link_libraries(mergesort gtest gmock gtest_main)

add_executable(quicksort quicksort.cpp)
target_link_libraries(quicksort gtest gmock gtest_main)

add_executable(heapsort heapsort.cpp)
target_link_libraries(heapsort gtest gmock gtest_main)

add_executable(counting_sort counting_sort.cpp)
target_link_libraries(counting_sort gtest gmock gtest_main)

add_executable(radix_sort radix_sort.cpp)
target_link_libraries(radix_sort gtest gmock gtest_main)

add_executable(bucket_sort bucket_sort.cpp)
target_link_libraries(bucket_sort gtest gmock gtest_main)