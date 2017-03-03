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
        binary_search.cpp
        # binary_search_st.cpp
        bubble_sort.cpp
        bucket_sort.cpp
        count_unique.cpp
        counting_sort.cpp
        dfs_spec.cpp
        graph_spec.cpp
        heapsort.cpp
        index_min_pq.cpp
        insertion_sort.cpp
        mergesort.cpp
        priority_queue_array.cpp
        quicksort.cpp
        radix_sort.cpp
        selection_sort.cpp
        shellsort.cpp)

set(ALL_TEST_LIBS
        gtest
        gmock
        graph
        dfs)

add_executable(test_all test_all.cpp ${ALL_TESTS})
target_link_libraries(test_all ${ALL_TEST_LIBS})

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

# priority queues
add_executable(priority_queue_array priority_queue_array.cpp)
target_link_libraries(priority_queue_array gtest gmock gtest_main)

add_executable(index_min_pq index_min_pq.cpp)
target_link_libraries(index_min_pq gtest gmock gtest_main)

# search tables
add_executable(hash_functions hash_functions.cpp)
target_link_libraries(hash_functions gtest gmock gtest_main)

add_library(sequential_search INTERFACE)
target_include_directories(sequential_search INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
# target_sources(sequential_search INTERFACE Sequential_search_st.h)
# set_target_properties(sequential_search PROPERTIES LINKER_LANGUAGE CXX)
add_executable(sequential_search_spec sequential_search_spec.cpp)
target_link_libraries(sequential_search_spec sequential_search gtest gmock gtest_main)

add_library(separate_chaining INTERFACE)
target_include_directories(separate_chaining INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
# target_sources(separate_chaining INTERFACE Separate_chaining_hash_st.h)
# set_target_properties(separate_chaining PROPERTIES LINKER_LANGUAGE CXX)
add_executable(separate_chaining_spec separate_chaining_spec.cpp)
target_link_libraries(separate_chaining_spec separate_chaining sequential_search gtest gmock gtest_main)

add_library(linear_probing INTERFACE)
target_include_directories(linear_probing INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(linear_probing_spec linear_probing_spec.cpp)
target_link_libraries(linear_probing_spec linear_probing gtest gmock gtest_main)

add_executable(binary_search_st binary_search_st.cpp)
target_link_libraries(binary_search_st gtest gmock gtest_main)

# general search
add_executable(binary_search binary_search.cpp)
target_link_libraries(binary_search gtest gmock gtest_main)

# string ops
add_executable(count_unique count_unique.cpp)
target_link_libraries(count_unique gtest gmock gtest_main)

# divide-and-conquer
add_executable(max_subarray max_subarray.cpp)
target_link_libraries(max_subarray gtest gmock gtest_main)

# permutations
add_executable(permutations permutations.cpp)
target_link_libraries(permutations gtest gmock gtest_main)

# partitions
add_executable(partitions partitions.cpp)
target_link_libraries(partitions gtest gmock gtest_main)

# graphs
add_library(graph Graph.h Graph.cpp)
add_executable(graph_spec graph_spec.cpp)
target_link_libraries(graph_spec graph gtest gmock gtest_main)

add_library(dfs Depth_first_search.cpp Depth_first_search.h)
add_executable(dfs_spec dfs_spec.cpp)
target_link_libraries(dfs_spec dfs graph gtest gmock gtest_main)

