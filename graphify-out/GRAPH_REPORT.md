# Graph Report - leetcode_c  (2026-10-26)

## Corpus Check
- Corpus is ~41,833 words - fits in a single context window. You may not need a graph.

## Summary
- 666 nodes · 1194 edges · 62 communities (58 shown, 4 thin omitted)
- Extraction: 93% EXTRACTED · 7% INFERRED · 0% AMBIGUOUS · INFERRED: 80 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- JSON-to-Map Handle
- Project Docs & CMake Build
- GitHub Actions Workflow
- File Module
- C++ Solutions & Wrapper
- JSON Parsing Helper
- json.h Parser (json2map)
- json.h Parser (json dir)
- Vector Storing Helper
- json.h Extract API (json dir)
- Parse Flags (json2map)
- Parse Flags (json dir)
- Logging (log.c)
- Map Container (rxi/map)
- json.h Extract API (json2map)
- Array & C Solutions
- Problems API Adapters
- Parse Errors (json2map)
- Parse Errors (json dir)
- Parse State (json2map)
- Parse State (json dir)
- Linked List & AddTwoNumbers
- Min Size Subarray Sum
- Windows Plat Time & LCP
- JSON Writers (json2map)
- JSON Writer Sizes (json dir)
- Vector Container (rxi/vec)
- JSON Types (json2map)
- JSON Writer Sizes (json2map)
- JSON Types (json dir)
- JSON Writers (json dir)
- JSON Common Helpers
- Sorting Algorithms
- CI Screenshot (Actions.png)
- Parse Result (json2map)
- String Ex (json2map)
- Value Ex (json2map)
- Parse Result (json dir)
- String Ex (json dir)
- Value Ex (json dir)
- Search Insert Position
- Object Element (json2map)
- Object Element (json dir)
- Array Element (json2map)
- Array Struct (json2map)
- Extract Result (json2map)
- Extract State (json2map)
- Number Struct (json2map)
- Object Struct (json2map)
- String Struct (json2map)
- Value Struct (json2map)
- Array Element (json dir)
- Array Struct (json dir)
- Extract Result (json dir)
- Extract State (json dir)
- Number Struct (json dir)
- Object Struct (json dir)
- String Struct (json dir)
- Value Struct (json dir)

## God Nodes (most connected - your core abstractions)
1. `json_parse_flags_e` - 18 edges
2. `json_parse_flags_e` - 18 edges
3. `Root CMake project leetcode_c` - 18 edges
4. `command_handler()` - 16 edges
5. `logging static library target` - 14 edges
6. `json_parse_error_e` - 13 edges
7. `json_parse_error_e` - 13 edges
8. `json_2_map static library target` - 13 edges
9. `json_parse_state_s` - 12 edges
10. `check_json_2_map_handle()` - 12 edges

## Surprising Connections (you probably didn't know these)
- `map_set_json_array()` --calls--> `map_data_set_void_pointer()`  [INFERRED]
  json2map/src/map_setting_helper.c → map/src/map_data.c
- `main()` --calls--> `log_set_level()`  [INFERRED]
  main/src/main.c → logging/src/log.c
- `json static library target (not built)` --semantically_similar_to--> `json_2_map static library target`  [INFERRED] [semantically similar]
  json/CMakeLists.txt → json2map/CMakeLists.txt
- `do_TwoSum()` --calls--> `twoSum()`  [INFERRED]
  problems_api/src/do_problems_api.c → array/src/Array.c
- `command_handler()` --calls--> `do_AddTwoNumbers()`  [INFERRED]
  cmd_invoke/src/cmd_invoke.c → problems_api/src/do_problems_api.c

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **Static library modules built by the root CMake project** — array_cmakelists_array, linked_list_cmakelists_linked_list, logging_cmakelists_logging, file_module_cmakelists_file_module, map_cmakelists_map, vector_cmakelists_vector, json2map_cmakelists_json_2_map, cmd_invoke_cmakelists_cmd_invoke, problems_api_cmakelists_problems_api, sort_cmakelists_sort, plat_utility_cmakelists_plat_utility, problems_impl_cmakelists_prob_impl [EXTRACTED 1.00]
- **JSON input to solution dispatch chain** — main_cmakelists_main_leetcode, json2map_cmakelists_json_2_map, cmd_invoke_cmakelists_cmd_invoke, problems_api_cmakelists_problems_api, problems_impl_cmakelists_prob_impl [EXTRACTED 1.00]
- **Open source C libraries used by the SDK** — readme_sheredom_json_h, readme_rxi_map, readme_rxi_vec, readme_rxi_log_c [EXTRACTED 1.00]
- **CI pipeline: build then linux and windows tests** — actions_png_matrix_build, actions_png_matrix_linux_tests, actions_png_matrix_windows_tests [EXTRACTED 0.95]

## Communities (62 total, 4 thin omitted)

### Community 0 - "JSON-to-Map Handle"
Cohesion: 0.10
Nodes (29): check_json_2_map_handle(), create_json2map_handle(), destroy_json2map_handle(), json_2_map_get_all_keys_impl(), json_2_map_get_base_version_impl(), json_2_map_get_char_impl(), json_2_map_get_components_version(), json_2_map_get_double_impl() (+21 more)

### Community 1 - "Project Docs & CMake Build"
Cohesion: 0.12
Nodes (32): array static library target, GitHub Actions CI matrix (cases 1-3 per problem), LeetCode SDK project overview (C, JSON-driven), Build type config (Debug/Release, LOG_LEVEL, version defines), Root CMake project leetcode_c, OS_SYSTEM selection (windows/linux), UNIT_TESTS / LEETCODE_TESTS flags, cmd_invoke static library target (+24 more)

### Community 2 - "GitHub Actions Workflow"
Cohesion: 0.09
Nodes (31): runs-on, steps, strategy, env, BUILD_TYPE, jobs, build, linux-tests (+23 more)

### Community 3 - "File Module"
Cohesion: 0.16
Nodes (21): check_file_handle(), create_file_handle(), destroy_file_handle(), file_handle_get_base_version_impl(), file_handle_get_buffer_impl(), file_handle_get_integer_impl(), file_handle_get_read_file_stream_impl(), file_handle_get_string_impl() (+13 more)

### Community 4 - "C++ Solutions & Wrapper"
Cohesion: 0.11
Nodes (14): p3_Solution, sub_string, p48_Solution, create_p3_solution(), create_p48_solution(), delete_p3_solution(), delete_p48_solution(), p3_Solution::lengthOfLongestSubstring() (+6 more)

### Community 5 - "JSON Parsing Helper"
Cohesion: 0.13
Nodes (19): json_parse(), json_value_as_object(), delete_json_root(), extract_elemnts_to_map(), init_json_parsing(), json_parsing_save_map(), new_json_root(), traverse_nodes() (+11 more)

### Community 6 - "json.h Parser (json2map)"
Cohesion: 0.14
Nodes (21): is_valid_unquoted_key_char(), json_get_array_size(), json_get_key_size(), json_get_number_size(), json_get_object_size(), json_get_string_size(), json_get_value_size(), json_hexadecimal_digit() (+13 more)

### Community 7 - "json.h Parser (json dir)"
Cohesion: 0.16
Nodes (19): is_valid_unquoted_key_char(), json_get_array_size(), json_get_key_size(), json_get_number_size(), json_get_object_size(), json_get_string_size(), json_get_value_size(), json_hexadecimal_digit() (+11 more)

### Community 8 - "Vector Storing Helper"
Cohesion: 0.33
Nodes (15): allocate_vector(), check_buffer_overflow(), check_out_of_memory(), check_vector_type_valid(), clear_vector(), free_vector(), get_occupied_index(), get_vector() (+7 more)

### Community 9 - "json.h Extract API (json dir)"
Cohesion: 0.16
Nodes (10): json_extract_copy_value(), json_extract_get_array_size(), json_extract_get_number_size(), json_extract_get_object_size(), json_extract_get_string_size(), json_extract_get_value_size(), json_extract_value(), json_extract_value_ex() (+2 more)

### Community 10 - "Parse Flags (json2map)"
Cohesion: 0.11
Nodes (18): json_parse_flags_e, json_parse_flags_allow_c_style_comments, json_parse_flags_allow_equals_in_object, json_parse_flags_allow_global_object, json_parse_flags_allow_hexadecimal_numbers, json_parse_flags_allow_inf_and_nan, json_parse_flags_allow_json5, json_parse_flags_allow_leading_or_trailing_decimal_point (+10 more)

### Community 11 - "Parse Flags (json dir)"
Cohesion: 0.11
Nodes (18): json_parse_flags_e, json_parse_flags_allow_c_style_comments, json_parse_flags_allow_equals_in_object, json_parse_flags_allow_global_object, json_parse_flags_allow_hexadecimal_numbers, json_parse_flags_allow_inf_and_nan, json_parse_flags_allow_json5, json_parse_flags_allow_leading_or_trailing_decimal_point (+10 more)

### Community 13 - "Logging (log.c)"
Cohesion: 0.18
Nodes (10): file_callback(), init_event(), lock(), log_add_callback(), log_add_fp(), log_log(), log_set_level(), log_set_lock() (+2 more)

### Community 14 - "Map Container (rxi/map)"
Cohesion: 0.31
Nodes (12): map_addnode(), map_bucketidx(), map_deinit_(), map_get_(), map_getref(), map_hash(), map_iter_(), map_newnode() (+4 more)

### Community 15 - "json.h Extract API (json2map)"
Cohesion: 0.21
Nodes (8): json_extract_copy_value(), json_extract_get_array_size(), json_extract_get_number_size(), json_extract_get_object_size(), json_extract_get_string_size(), json_extract_get_value_size(), json_extract_value(), json_extract_value_ex()

### Community 16 - "Array & C Solutions"
Cohesion: 0.19
Nodes (4): twoSum(), delete_char_list(), new_char_list(), lengthOfLastWord()

### Community 17 - "Problems API Adapters"
Cohesion: 0.26
Nodes (10): command_handler(), do_json_2_map_test(), do_lengthOfLastWord(), do_LongestCommonPrefix(), do_LongestSubstringWithoutRepeating(), do_minSubArrayLen(), do_rotateImage(), do_searchInsert() (+2 more)

### Community 18 - "Parse Errors (json2map)"
Cohesion: 0.15
Nodes (13): json_parse_error_e, json_parse_error_allocator_failed, json_parse_error_expected_colon, json_parse_error_expected_comma_or_closing_bracket, json_parse_error_expected_opening_quote, json_parse_error_invalid_number_format, json_parse_error_invalid_string, json_parse_error_invalid_string_escape_sequence (+5 more)

### Community 19 - "Parse Errors (json dir)"
Cohesion: 0.15
Nodes (13): json_parse_error_e, json_parse_error_allocator_failed, json_parse_error_expected_colon, json_parse_error_expected_comma_or_closing_bracket, json_parse_error_expected_opening_quote, json_parse_error_invalid_number_format, json_parse_error_invalid_string, json_parse_error_invalid_string_escape_sequence (+5 more)

### Community 20 - "Parse State (json2map)"
Cohesion: 0.17
Nodes (12): json_parse_state_s, data, data_size, dom, dom_size, error, flags_bitset, line_no (+4 more)

### Community 21 - "Parse State (json dir)"
Cohesion: 0.17
Nodes (12): json_parse_state_s, data, data_size, dom, dom_size, error, flags_bitset, line_no (+4 more)

### Community 22 - "Linked List & AddTwoNumbers"
Cohesion: 0.26
Nodes (8): addTwoNumbers(), DeleteList(), GetListLength(), NewList(), NewNode(), PushNode(), TraversePrintNodes(), do_AddTwoNumbers()

### Community 23 - "Min Size Subarray Sum"
Cohesion: 0.39
Nodes (8): get_area(), get_lock(), get_window_length(), lock_side(), minSubArrayLen(), move_forward(), unlock_side(), update_min_len()

### Community 25 - "JSON Writers (json2map)"
Cohesion: 0.27
Nodes (10): json_write_minified(), json_write_minified_array(), json_write_minified_object(), json_write_minified_value(), json_write_number(), json_write_pretty(), json_write_pretty_array(), json_write_pretty_object() (+2 more)

### Community 26 - "JSON Writer Sizes (json dir)"
Cohesion: 0.27
Nodes (10): json_write_get_number_size(), json_write_get_string_size(), json_write_minified(), json_write_minified_get_array_size(), json_write_minified_get_object_size(), json_write_minified_get_value_size(), json_write_pretty(), json_write_pretty_get_array_size() (+2 more)

### Community 28 - "Vector Container (rxi/vec)"
Cohesion: 0.28
Nodes (4): vec_expand_(), vec_insert_(), vec_reserve_(), vec_reserve_po2_()

### Community 29 - "JSON Types (json2map)"
Cohesion: 0.25
Nodes (8): json_type_e, json_type_array, json_type_false, json_type_null, json_type_number, json_type_object, json_type_string, json_type_true

### Community 30 - "JSON Writer Sizes (json2map)"
Cohesion: 0.36
Nodes (8): json_write_get_number_size(), json_write_get_string_size(), json_write_minified_get_array_size(), json_write_minified_get_object_size(), json_write_minified_get_value_size(), json_write_pretty_get_array_size(), json_write_pretty_get_object_size(), json_write_pretty_get_value_size()

### Community 31 - "JSON Types (json dir)"
Cohesion: 0.25
Nodes (8): json_type_e, json_type_array, json_type_false, json_type_null, json_type_number, json_type_object, json_type_string, json_type_true

### Community 32 - "JSON Writers (json dir)"
Cohesion: 0.36
Nodes (8): json_write_minified_array(), json_write_minified_object(), json_write_minified_value(), json_write_number(), json_write_pretty_array(), json_write_pretty_object(), json_write_pretty_value(), json_write_string()

### Community 33 - "JSON Common Helpers"
Cohesion: 0.43
Nodes (3): JSON_dispatch_value_type(), JSON_extract_elements(), JSON_traverse_objects()

### Community 35 - "Sorting Algorithms"
Cohesion: 0.47
Nodes (3): bubble_sort(), selection_sort(), swap()

### Community 36 - "CI Screenshot (Actions.png)"
Cohesion: 0.40
Nodes (5): Actions.yml GitHub Actions workflow (on: push), All CI jobs passed (green checks), Matrix: build (ubuntu-latest 24s, windows-latest 1m 31s), Matrix: linux-tests (AddTwoNumbers, LongestSubstring, TwoSum), Matrix: windows-tests (AddTwoNumbers, LongestSubstring, TwoSum)

### Community 37 - "Parse Result (json2map)"
Cohesion: 0.40
Nodes (5): json_parse_result_s, error, error_line_no, error_offset, error_row_no

### Community 38 - "String Ex (json2map)"
Cohesion: 0.40
Nodes (5): json_string_ex_s, line_no, offset, row_no, string

### Community 39 - "Value Ex (json2map)"
Cohesion: 0.40
Nodes (5): json_value_ex_s, line_no, offset, row_no, value

### Community 40 - "Parse Result (json dir)"
Cohesion: 0.40
Nodes (5): json_parse_result_s, error, error_line_no, error_offset, error_row_no

### Community 41 - "String Ex (json dir)"
Cohesion: 0.40
Nodes (5): json_string_ex_s, line_no, offset, row_no, string

### Community 42 - "Value Ex (json dir)"
Cohesion: 0.40
Nodes (5): json_value_ex_s, line_no, offset, row_no, value

### Community 43 - "Search Insert Position"
Cohesion: 0.60
Nodes (3): binary_search(), not_found_insert(), searchInsert()

### Community 44 - "Object Element (json2map)"
Cohesion: 0.50
Nodes (4): json_object_element_s, name, next, value

### Community 45 - "Object Element (json dir)"
Cohesion: 0.50
Nodes (4): json_object_element_s, name, next, value

### Community 46 - "Array Element (json2map)"
Cohesion: 0.67
Nodes (3): json_array_element_s, next, value

### Community 47 - "Array Struct (json2map)"
Cohesion: 0.67
Nodes (3): json_array_s, length, start

### Community 48 - "Extract Result (json2map)"
Cohesion: 0.67
Nodes (3): json_extract_result_s, data_size, dom_size

### Community 49 - "Extract State (json2map)"
Cohesion: 0.67
Nodes (3): json_extract_state_s, data, dom

### Community 50 - "Number Struct (json2map)"
Cohesion: 0.67
Nodes (3): json_number_s, number, number_size

### Community 51 - "Object Struct (json2map)"
Cohesion: 0.67
Nodes (3): json_object_s, length, start

### Community 52 - "String Struct (json2map)"
Cohesion: 0.67
Nodes (3): json_string_s, string, string_size

### Community 53 - "Value Struct (json2map)"
Cohesion: 0.67
Nodes (3): json_value_s, payload, type

### Community 54 - "Array Element (json dir)"
Cohesion: 0.67
Nodes (3): json_array_element_s, next, value

### Community 55 - "Array Struct (json dir)"
Cohesion: 0.67
Nodes (3): json_array_s, length, start

### Community 56 - "Extract Result (json dir)"
Cohesion: 0.67
Nodes (3): json_extract_result_s, data_size, dom_size

### Community 57 - "Extract State (json dir)"
Cohesion: 0.67
Nodes (3): json_extract_state_s, data, dom

### Community 58 - "Number Struct (json dir)"
Cohesion: 0.67
Nodes (3): json_number_s, number, number_size

### Community 59 - "Object Struct (json dir)"
Cohesion: 0.67
Nodes (3): json_object_s, length, start

### Community 60 - "String Struct (json dir)"
Cohesion: 0.67
Nodes (3): json_string_s, string, string_size

### Community 61 - "Value Struct (json dir)"
Cohesion: 0.67
Nodes (3): json_value_s, payload, type

## Ambiguous Edges - Review These
- `Root CMake project leetcode_c` → `json static library target (not built)`  [AMBIGUOUS]
  CMakeLists.txt · relation: references

## Knowledge Gaps
- **163 isolated node(s):** `json_parse_flags_default`, `json_parse_flags_allow_trailing_comma`, `json_parse_flags_allow_unquoted_keys`, `json_parse_flags_allow_global_object`, `json_parse_flags_allow_equals_in_object` (+158 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 237 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **4 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `json_parse_flags_e` connect `Parse Flags (json2map)` to `json.h Extract API (json2map)`?**
  _High betweenness centrality (0.045) - this node is a cross-community bridge._
- **What connects `json_parse_flags_default`, `json_parse_flags_allow_trailing_comma`, `json_parse_flags_allow_unquoted_keys` to the rest of the system?**
  _163 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `JSON-to-Map Handle` be split into smaller, more focused modules?**
  _Cohesion score 0.09871794871794871 - nodes in this community are weakly interconnected._
- **Why does `json_parse_flags_e` connect `Parse Flags (json dir)` to `json.h Extract API (json dir)`?**
  _High betweenness centrality (0.045) - this node is a cross-community bridge._
- **Should `Project Docs & CMake Build` be split into smaller, more focused modules?**
  _Cohesion score 0.11740890688259109 - nodes in this community are weakly interconnected._
- **Why does `json_parse_error_e` connect `Parse Errors (json2map)` to `json.h Extract API (json2map)`?**
  _High betweenness centrality (0.032) - this node is a cross-community bridge._

### Low-confidence Hints
_AMBIGUOUS edges — the extractor was unsure. Verify before acting on these._

- **What is the exact relationship between `Root CMake project leetcode_c` and `json static library target (not built)`?**
  _Edge tagged AMBIGUOUS (relation: references) - confidence is low._