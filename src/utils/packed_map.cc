//
// Created by zhao on 23-4-25.
//

#ifndef DATABASE_INTERNAL_PACKED_MAP_CC
#define DATABASE_INTERNAL_PACKED_MAP_CC

#include "packed_map.h"
#include <cassert>
#include <cstring>

namespace di {

namespace packed_map_detail {
static unsigned Min(unsigned a, unsigned b) { return a < b ? a : b; }
} // namespace packed_map_detail

template <uint16_t ManSizeBytes>
PackedMap<ManSizeBytes>::PackedMap(const uint8_t *lower_key,
                                   unsigned lower_key_length,
                                   const uint8_t *upper_key,
                                   unsigned upper_key_length) {
  // 比较lower_key,和upper_key两个存储区大小
  // 比较前Min()个字节
  const int cmp =
      memcmp(lower_key, upper_key,
             packed_map_detail::Min(lower_key_length, upper_key_length));
  assert(cmp < 0 || (cmp == 0 && lower_key_length < upper_key_length) ||
         upper_key_length == 0);
  SetFence(lower_key, lower_key_length, upper_key, upper_key_length);
}

template <uint16_t MapSizeBytes>
void PackedMap<MapSizeBytes>::SetFence(const uint8_t *lower_key,
                                       unsigned int lower_key_length,
                                       const uint8_t *upper_key,
                                       unsigned int upper_key_length) {
  InsertFence(header_.lower_fence, lower_key, lower_key_length);
  InsertFence(header_.upper_fence, upper_key, upper_key_length);
}

template <uint16_t MapSizeBytes>
void PackedMap<MapSizeBytes>::InsertFence(typename Header::FenceKeySlot &fk,
                                          const uint8_t *key,
                                          unsigned int key_length) {
  assert(FreeSpace() >= key_length);
  header_.data_offset -= key_length;
  header_.space_used += key_length;
  fk.offset = header_.data_offset;
  fk.length = key_length;
  memcpy(Ptr() + header_.data_offset, key, key_length);
}

template <uint16_t MapSizeBytes>
unsigned int PackedMap<MapSizeBytes>::FreeSpace() {
  return header_.data_offset -
         (reinterpret_cast<uint8_t *>(slot_ + header_.count) - Ptr());
}

template <uint16_t MapSizeBytes> uint8_t *PackedMap<MapSizeBytes>::Ptr() {
  return reinterpret_cast<uint8_t *>(this);
}

template <uint16_t MapSizeBytes>
const uint8_t *PackedMap<MapSizeBytes>::Ptr() const {
  return reinterpret_cast<const uint8_t *>(this);
}

} // namespace di
#endif // DATABASE_INTERNAL_PACKED_MAP_CC
