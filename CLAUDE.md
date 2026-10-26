# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A "LeetCode SDK" written deliberately in C (with a little C++ in `problems_impl`): each problem's input is stored as a JSON file in `problems/`, and the `main_leetcode` executable parses it and dispatches to the matching solution. Must build on both Windows (MSVC) and Linux (gcc). README.md is in Traditional Chinese.

## Build, run, test

```
cmake -B build -DCMAKE_BUILD_TYPE=Release     # Debug also supported (enables LOG_LEVEL debug + MSVC CRT leak detection)
cmake --build build --config Release
ctest -C Release --test-dir build              # only unit tests: tests/time sleep tests (timeout_test_0..5), ~15s
```

- All libs and the `main_leetcode` binary are emitted to `<repo>/bin/` (MSVC multi-config adds a `Release/` or `Debug/` subfolder), not the build dir.
- Run a problem: `bin/main_leetcode -j problems/<Name>_case_<N>.json` (`bin\Release\main_leetcode.exe` on Windows). `main.c` reads `argv[2]` as the path; `argv[1]` is ignored.
- There is no per-problem assertion test: CI "tests" just run each case JSON and check the process runs; correctness is read from the logged output. `.github/workflows/Actions.yml` builds on ubuntu+windows, then runs cases 1–3 of each problem in a matrix.
- Formatting: `.clang-format` (Google base, 4-space indent, 100 cols, left pointer alignment).

## Architecture

Flow: `main` → `create_json2map_handle` (JSON file → `map`/`vec` containers) → reads `problem_id` → `command_handler(cmd_id, ...)` → big `switch` in `cmd_invoke/src/cmd_invoke.c` → `do_<Problem>()` in `problems_api` → actual solution in `problems_impl`.

Modules are each a static library with their own `CMakeLists.txt` (`enc/` = public headers, `inc/` = private headers, `src/`):
- `json2map` – parses JSON (sheredom json.h) into an `ijson_2_map_t` object (function-pointer "interface" struct: `map_get_int`, `map_get_vector_int`, `map_get_all_keys`, ...). Uses `map` (rxi/map) and `vector` (rxi/vec) as ANSI-C containers.
- `cmd_invoke` – command pattern dispatcher; `commands.h` holds the `cmd_id` enum (LeetCode problems use their LeetCode number; sort algorithms use `ALG_BASE`=4000+; `problem_id` 0 is the json2map test).
- `problems_api` – `do_*` adapters: pull inputs from the map by key, log "Input/Output Information", call the solution, time it, free memory.
- `problems_impl` – the actual solutions. Most are C; some (e.g. problems 3, 48) are C++ classes exposed to C via `problems_cxximpl.cpp` + `problems_wrapper.{h,c}` (`*_ex` functions).
- `array`, `linked_list`, `sort` – shared data structures/algorithms used by solutions; `logging` (rxi/log.c); `file_module`; `plat_utility` (`plat_time`/`plat_memory`, with `_windows.c`/`_linux.c` variants selected per OS — keep both in sync).
- `json/` is not built (commented out in the root CMakeLists).

## Adding a new LeetCode problem

Follow the pattern in the history (one commit per step, e.g. problem 209):
1. `problems_impl/src/<Name>.c` + `problems_impl/enc/<Name>.h`, and add the .c to `problems_impl/CMakeLists.txt`.
2. `do_<fn>` in `problems_api/src/do_problems_api.c` + declaration in `problems_api/enc/do_problems_api.h`.
3. Add `CMD_LEETCODE_*` to `cmd_invoke/inc/commands.h` and a `case` in `command_handler`.
4. Add `problems/<Name>_case_{1,2,3}.json` with `"problem_id"` plus the input keys (the CI matrix expects exactly three cases per name).
5. Add `<Name>` to the `problem:` matrix in **both** the `windows-tests` and `linux-tests` jobs of `Actions.yml`.

## Gotchas

- Build type sets `LOG_LEVEL` (Debug=1, Release=2, mirroring `logging/enc/log.h`) and `_DEBUG_VERSION`/`_RELEASE_VERSION`; MSVC Debug also defines `_CRTDBG_MAP_ALLOC`, and `main.c` then dumps memory leaks — new code must free what it allocates.
- `LEETCODE_TESTS` and `UNIT_TESTS` in the root CMakeLists are hard-set to 1, so `main` and `tests/` are always built.
- Windows targets need `_CRT_SECURE_NO_WARNINGS` (already added per-module under `if(MSVC)`).

## graphify

This project has a knowledge graph at graphify-out/ with god nodes, community structure, and cross-file relationships.

Rules:
- When graphify-out/graph.json exists, run `graphify query "<question>"` before your first grep, search or source-file read for a codebase question, and put this rule in every subagent prompt that explores code. Read raw files only for lines the graph or an earlier read already located. Use `graphify path "<A>" "<B>"` for relationships and `graphify explain "<concept>"` for focused concepts. These return a scoped subgraph, usually much smaller than GRAPH_REPORT.md or raw grep output.
- If graphify-out/wiki/index.md exists, use it for broad navigation instead of raw source browsing.
- Read graphify-out/GRAPH_REPORT.md only for broad architecture review or when query/path/explain do not surface enough context.
- After modifying code, run `graphify update .` to keep the graph current (AST-only, no API cost).
- A committed graphify-out/graph.json is rewritten whole on every build, so a large diff to it in a pull request is expected. Do not flag it as churn or suggest skipping the graph rebuild or its hooks.
