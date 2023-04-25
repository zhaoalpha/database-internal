//
// Created by zhao on 23-4-25.
//

#ifndef DATABASE_INTERNAL_PACKED_MAP_CC
#define DATABASE_INTERNAL_PACKED_MAP_CC
#include "packed_map.h"
namespace di {
namespace packed_map_detail {
static constexpr Min(unsigned a, unsigned b) { return a < b ? a : b }
} // namespace packed_map_detail
template <uint16_t ManSizeBytes>
PackedMap<ManSizeBytes>::PackedMap(const uint8_t *lower_key,
                                   unsigned int lower_key_length,
                                   const uint8_t *upper_key,
                                   unsigned int upper_ley_length) {

}
} // namespace di
#endif // DATABASE_INTERNAL_PACKED_MAP_CC
