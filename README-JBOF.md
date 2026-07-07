# astra-sim-jbof — ASTRA-Sim with the JBOF memory tier (flattened snapshot)

A **flattened snapshot** of ASTRA-Sim (nested submodules materialized as regular files) that
serves as the analytical timing backend for **DevHSA/Storage-for-AI** (LLMServingSim). It adds a
vendor-neutral **JBOF** (pooled-flash) KV-cache tier to the analytical memory model.

## What changed vs upstream `casys-kaist/astra-sim`
- New memory location **`JBOF_MEMORY`** (`astra-sim/system/AstraMemoryAPI.hh`) alongside
  FLASH/COLDSTORE, wired through `astra-sim/system/Sys.{hh,cc}` and `astra-sim/workload/Workload.cc`.
- `extern/memory_backend/analytical/AnalyticalMemory.{cc,hh}`: JBOF handling plus a network-link
  term (`link_latency + bytes/link_bw`) for pooled tiers reached over a BlueField/RDMA fabric.
- Both analytical frontends
  (`astra-sim/network_frontend/analytical/congestion_{aware,unaware}/main.cc`) parse a
  `jbof_mem` block from `memory_expansion.json`.
- Chakra converter (`extern/graph_frontend/chakra/src/converter/llm_converter.py`): the `JBOF`
  trace tag maps to `JBOF_MEMORY`, so a deep-tier prefix reload becomes a real, contention-timed
  `MEM_LOAD` node.

## Build (analytical backend)
```bash
bash build/astra_analytical/build.sh
```
Requires a C++ toolchain + protobuf/protoc. If the Chakra protobuf bindings error with a
gencode/runtime mismatch, run `pip3 install --upgrade protobuf`.

## Notes
- The `ns-3` / `csg-htsim` network backends and the generated `inputs/` and compiled
  `build/astra_analytical/build/` directories are intentionally omitted — they are not needed to
  compile and run the analytical examples.
- This snapshot is referenced by `DevHSA/Storage-for-AI` as the `astra-sim` submodule.
