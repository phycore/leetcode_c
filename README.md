# LeetCode SDK
簡易的 LeetCode SDK 目的是整合所有練習過的題目與快速執行，將 LeetCode 的題目以 JSON 檔案格式儲存，執行應用程式時解析 JSON 檔案內容與分配執行對應的 LeetCode 問題，順帶練習 C 語言獨立構專案整合各模組的過程。

# 安裝與執行應用程式
Windows/Linux 可跨平台使用，Git clone 或下載此專案後，請使用 [CMake](https://cmake.org/) 編譯，各模組皆獨立編譯成 library，再由[主程式](https://github.com/phycore/leetcode_c/blob/main/main/src/main.c)控制，如何執行可參考 [Actions.yml](https://github.com/phycore/leetcode_c/blob/main/.github/workflows/Actions.yml)
- Windows
```
.\main_leetcode.exe -j TwoSum_case_1.json
```

- Linux
```
./main_leetcode -j TwoSum_case_1.json
```
# 使用方法
1. 將 leetcode 題目儲存成 JSON 檔案
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

2. 利用 json_2_map 模組把 json 檔案轉儲存成 map 資料結構，並可取得對應的 keys, values
```C
    // 代入 json 檔案路徑並創建 json_2_map 物件
    ijson_2_map_t* ijson_2_map =
            create_json2map_handle((void*)file_path, J2MAP_CREATE_MODE_FILE_PATH);

    // 創建指標陣列 key_list: keys 所需記憶體
    // (略)

    // 利用 json_2_map 物件的 map_get_all_keys() 取得所有的 keys
    ijson_2_map->map_get_all_keys(ijson_2_map, keys, &size_of_keys);
    for (size_t keys_idx = 0; keys_idx < size_of_keys; keys_idx++) {
        log_debug("key[%d]: %s", keys_idx, keys[keys_idx]);
    }

    // 取得 json_2_map 物件儲存的 keys, values
    char* problem_id = "problem_id";
    int32_t id = 0;
    ijson_2_map->map_get_int(ijson_2_map, problem_id, &id);

    char* target = "target";
    int32_t target_val = 0;
    ijson_2_map->map_get_int(ijson_2_map, target, &target_val);

    char* nums = "nums";
    vec_int_t* nums_val = (vec_int_t*)ijson_2_map->map_get_vector_int(ijson_2_map, nums);
    if (NULL != nums_val) {
        for (int idx = 0; idx < nums_val->length; idx++) {
            log_debug("%s[%d]= %d", nums, idx, nums_val->data[idx]);
        }
    }

    // 釋放指標陣列 key_list: keys 記憶體
    // (略)

    // 使用完畢，清除 json_2_map 物件
    destroy_json2map_handle(ijson_2_map);
```

# 待完成
1. 分配與執行 leetocde 題目對應的程式碼。
1. 輸出 log 儲存成檔案。
1. leetcode 問題解答，執行效能的軟體時間量測。
1. leetcode 問題解答，執行效能的 code size 計算。

# 使用開源專案
1. json: https://github.com/sheredom/json.h
1. map: https://github.com/rxi/map
1. vector: https://github.com/rxi/vec
1. logging: https://github.com/rxi/log.c