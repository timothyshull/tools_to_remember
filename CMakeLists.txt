cmake_minimum_required(VERSION 3.6)
project(tools_to_remember)

set(CMAKE_CXX_STANDARD 11)

add_executable(binary_search binary_search.cpp)
add_executable(binary_search_bst binary_search_bst.cpp)
add_executable(case_find case_find.cpp)
add_executable(count_unique count_unique.cpp)
add_executable(cycle cycle.cpp)
add_executable(deadlock_cycle deadlock_cycle.cpp)
add_executable(directed_cycle directed_cycle.cpp)
add_executable(file_manip_todo file_manip_todo.cpp)
add_executable(file_word_count file_word_count.cpp)
add_executable(gcd gcd.cpp)
add_executable(graph_bfs graph_bfs.cpp)
add_executable(graph_dfs graph_dfs.cpp)
add_executable(graph_print graph_print.cpp)
add_executable(join_strings join_strings.cpp)
add_executable(knapsack knapsack.cpp)
add_executable(lexicographical_compare lexicographical_compare.cpp)
add_executable(levenshtein_distance levenshtein_distance.cpp)
add_executable(list_reverse list_reverse.cpp)
add_executable(margins_and_justify margins_and_justify.cpp)
add_executable(nth_substring nth_substring.cpp)
add_executable(pad_string pad_string.cpp)
add_executable(quicksort quicksort.cpp)
add_executable(remove_substrings remove_substrings.cpp)
add_executable(simple_path simple_path.cpp)
add_executable(split_string split_string.cpp)
add_executable(stream_read_string stream_read_string.cpp)
add_executable(tabs_to_spaces tabs_to_spaces.cpp)
add_executable(text_wrap text_wrap.cpp)
add_executable(tokenize_string tokenize_string.cpp)
add_executable(topological topological.cpp)
add_executable(topological_acpp topological_acpp.cpp)
add_executable(tree_nodes_within_distance tree_nodes_within_distance.cpp)
add_executable(tree_print tree_print.cpp)
add_executable(tree_traversal tree_traversal.cpp)
add_executable(trim_string trim_string.cpp)