# LeetCode SDK
  簡易的 LeetCode SDK 目的是整合所有練習過的題目可以快速執行，將 LeetCode 的題目先以 [JSON](https://www.json.org/json-en.html) 檔案格式儲存，執行應用程式將解析輸入的 [JSON](https://www.json.org/json-en.html) 檔案並藉由[命令模式](https://en.wikipedia.org/wiki/Command_pattern)分配且執行對應的 LeetCode 問題解答。

  將一些常見的軟體應用**刻意**使用 C 語言撰寫，順便練習獨立建構專案、整合各模組的過程。

# 安裝與執行
Windows/Linux 可跨平台使用，Git clone 或下載此專案後，請使用 [CMake](https://cmake.org/) 建置專案，各模組皆獨立編譯成 .lib 或 .a，再由[主程式](https://github.com/phycore/leetcode_c/blob/main/main/src/main.c)呼叫，執行應用程式如下範例或是參考 [Actions.yml](https://github.com/phycore/leetcode_c/blob/main/.github/workflows/Actions.yml)。
- Windows
```
.\main_leetcode.exe -j TwoSum_case_1.json
```

- Linux
```
./main_leetcode -j TwoSum_case_1.json
```
# 使用方式
1. 將 LeetCode 題目儲存成 JSON 檔案
  - [Two Sum](https://leetcode.com/problems/two-sum/) 問題與範例解答<br>
  Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.<br>
  ```
  Input: nums = [2,7,11,15], target = 9
  Output: [0,1]
  Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
  ```
  - 題目提供的資訊以 JSON 檔案格式儲存
```json
{
  "problem_id": 1,
  "target": 9,
  "nums": [
    2,
    7,
    11,
    15
  ]
}
```

2. 主程式介面
```C
    // 代入 json 檔案路徑並創建 json_2_map 物件
    ijson_2_map_t* ijson_2_map = create_json2map_handle((void*)file_path, J2MAP_CREATE_MODE_FILE_PATH);

    // 利用 json_2_map 物件，取得問題編號 key: prblem_id 對應的 value，且以 cmd_id 整數變數儲存。
    ijson_2_map->map_get_int(ijson_2_map, "problem_id", &cmd_id);

    // 將 cmd_id 代入命令模式處理器即可執行對應的 LeetCode 問題解答
    retval = command_handler(cmd_id, &in_data, &out_data);

    // 使用完畢，清除 json_2_map 物件
    destroy_json2map_handle(ijson_2_map);
```

3. 輸出答案
  - [Two Sum](https://leetcode.com/problems/two-sum/) 經 LeetCode SDK 執行時輸出的問題資訊與解答
```shell
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/file_module/src/file_module.c:214: File: TwoSum_case_1.json open with "r" mode.
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/file_module/src/file_utils.c:21: get_file_size, file_size = 82 bytes
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/cmd_invoke/src/cmd_invoke.c:33: command_handler, process problem cmd_id: 1
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/map/src/map_data.c:308: map_data_get_keys, get key[0]: nums
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/map/src/map_data.c:312: map_data_get_keys, get key[1]: target
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/map/src/map_data.c:312: map_data_get_keys, get key[2]: problem_id
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:54: Begin Input Information:
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:56: do_TwoSum, Input: nums[0] = 2
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:56: do_TwoSum, Input: nums[1] = 7
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:56: do_TwoSum, Input: nums[2] = 11
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:56: do_TwoSum, Input: nums[3] = 15
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:58: do_TwoSum, target = 9
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:59: End Input Information:

15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:61: Begin Output Information:
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:64: do_TwoSum, Output: index_array[0] = 0
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:64: do_TwoSum, Output: index_array[1] = 1
15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/problems_api/src/do_problems_api.c:66: End Output Information:

15:41:45 INFO  /home/runner/work/leetcode_c/leetcode_c/cmd_invoke/src/cmd_invoke.c:68: command_handler, process problem cmd_id: 1 and retval = 0
```

4. 主要功能模組說明
  - json_2_map 可以解析 JSON 檔案內容並轉儲存成 map 資料結構
```C
    // json_2_map 物件實例化時就已經把代入的 JSON 檔案解析出所有內容並存成 map
    // ANSI C 並無像 C++ 的 map container，所以使用開源專案的 map in C
    ijson_2_map_t* ijson_2_map = create_json2map_handle((void*)file_path, J2MAP_CREATE_MODE_FILE_PATH);
```
  - 藉由 json_2_map 物件定義好的方法(methods) 取得 keys, value
```C
    // 取得所有的 key 儲存在 char** 指標陣列 in_list ，並記錄 list 長度即 key 的總數目於 in_list_len 變數中
    ijson_2_map->map_get_all_keys(ijson_2_map, in_list, (uint32_t*)&in_list_len);

    // 遍歷指標陣列 in_list 存放所有的 keys，取得所屬問題的 key, value
    int32_t problem_id = 0;
    int32_t target = 0;
    // ANSI C 沒有 C++ 的 vector container，所以使用開源專案的 vector in C
    vec_int_t* nums_val = NULL;
    for (size_t keys_idx = 0; keys_idx < in_list_len; keys_idx++) {
        // 取得 key: prblem_id 對應的 value
        if (0 == strcmp(in_list[keys_idx], "problem_id")) {
            ijson_2_map->map_get_int(ijson_2_map, in_list[keys_idx], &problem_id);
        }

        // 取得 key: target 對應的 value
        if (0 == strcmp(in_list[keys_idx], "target")) {
            ijson_2_map->map_get_int(ijson_2_map, in_list[keys_idx], &target);
        }
        // 取得 key: nums 對應的 value
        if (0 == strcmp(in_list[keys_idx], "nums")) {
            nums_val = ijson_2_map->map_get_vector_int(ijson_2_map, in_list[keys_idx]);
            numsSize = nums_val->length;
        }
    }
```

# 待完成
1. 將螢幕輸出的 log 儲存成文字檔案。
1. LeetCode 問題解答，執行效能的軟體時間量測。
1. LeetCode 問題解答，執行效能的記憶體使用量。
1. LeetCode 問題解答，程式碼大小的 code size 計算。

# 使用開源專案
1. C 語言解析 JSON: https://github.com/sheredom/json.h
1. C 語言 map 資料結構: https://github.com/rxi/map
1. C 語言 vector 資料結構: https://github.com/rxi/vec
1. C 語言 logging 日誌: https://github.com/rxi/log.c