/******************************************************************************
This source code is licensed under the MIT license found in the
LICENSE file in the root directory of this source tree.
*******************************************************************************/

#ifndef __ASTRA_MEMORY_API_HH__
#define __ASTRA_MEMORY_API_HH__

#include <cstdint>

namespace AstraSim {

enum class MemoryLocationType : uint8_t {
  INVALID_MEMORY = 0,
  LOCAL_MEMORY = 1,
  REMOTE_MEMORY = 2,
  CXL_MEMORY = 3,
  STORAGE_MEMORY = 4,
  // Deep spill tiers (LLMServingSim tiered-memory extension). Must match the
  // MemoryType enum in chakra/src/converter/llm_converter.py.
  FLASH_MEMORY = 5,
  JBOF_MEMORY = 6,
  COLDSTORE_MEMORY = 7
};

class Sys;
class WorkloadLayerHandlerData;

class AstraMemoryAPI {
  public:
    virtual ~AstraMemoryAPI() = default;
    virtual void set_sys(int id, Sys* sys) = 0;
    virtual void issue(uint64_t tensor_size,
                       WorkloadLayerHandlerData* wlhd) = 0;
    
    virtual MemoryLocationType get_memory_location_type() const = 0;
};

}  // namespace AstraSim

#endif /* __ASTRA_MEMORY_API_HH__ */
