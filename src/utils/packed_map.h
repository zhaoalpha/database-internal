//
// Created by zhao on 23-4-25.
//

#ifndef DATABASE_INTERNAL_PACKED_MAP_H
#define DATABASE_INTERNAL_PACKED_MAP_H

#pragma once
#include <cstddef>
#include <cstdint>
namespace di {
// PackedMap可以在编译期间进行配置，但是要严格小于64KB
// Key最大大小由kMaxKeySizeBytes指定
// 为了使用前缀编码，key的范围必须指定，所以要知道最大Key和最小的Key
// 提供8字节供存储溢出页的元信息
// 不是线程安全的需要外部进行互斥
template <uint16_t MapSizeBytes> class PackedMap {
public:
  static_assert(MapSizeBytes % 8 == 0,
                "The PackedMap must have a size that is divisible by 8");

  PackedMap() = default;

  // 创建有边界的PackedMap
  // 这样能在之后插入key更加高效的进行encode
  // 所有key必须满足 lower_key <= key <= upper_key
  // 如果违反此约定，会发生未定义事件
  // 可以将upper_key_length设置为0，放弃更加高效的编码方式
  PackedMap(const uint8_t *lower_key, unsigned lower_key_length,
            const uint8_t *upper_key, unsigned upper_ley_length);

  // 插入key和payload
  // 重复的key会覆盖payload
  bool Insert(const uint8_t *key, unsigned key_length, const unsigned payload,
              const unsigned payload_length);

private:
  static constexpr unsigned kHintCount = 16;
  static constexpr uint8_t kValidFlag = 1;
  static constexpr uint8_t kOverFlowFlag = 2;

  struct Header {
    // 记录key的起始位置和长度
    struct FenceKeySlot {
      uint16_t offset;
      uint16_t length;
    };
    // 记录在该page中max key 和 min key
    // 所有key在区间[lower_fence,upper_fence]
    FenceKeySlot lower_fence = {0, 0};
    FenceKeySlot upper_fence = {0, 0};
    uint16_t count = 0;
    // 当前map已经用空间大小
    uint16_t space_used = 0;
    // data是从后向前增长的
    uint16_t data_offset = MapSizeBytes;
  };

  struct Slot {
    uint16_t offset;
    uint16_t key_length;
    uint16_t payload_length;
    // TODO：设计原因
    union {
      uint32_t head;
      uint8_t head_bytes[4];
    };
  } __attribute__((packed));

  Header header_;
  // 用于内存对齐，保证剩余空间能装下整个slot
  uint8_t pending_[(MapSizeBytes - sizeof(Header) % sizeof(Slot))];

  static constexpr unsigned kTotalMetadataBytes =
      sizeof(Header) + sizeof(pending_);

  // ToDO 为什么又选择union
  union {
    // slot数组 从前向后增长
    Slot slot_[(MapSizeBytes - sizeof(Header)) / sizeof(Slot)];
    // 从后向前增长
    uint8_t heap_[10];
    l
  };

  static_assert((MapSizeBytes - kTotalMetadataBytes) % sizeof(Slot) == 0);

  static_assert(MapSizeBytes > kTotalMetadataBytes,
                "The PackedMap must be large enough to store its header");

public:
  static constexpr size_t kMaxKeySizeByte =
      (MapSizeBytes - kTotalMetadataBytes - (2 * sizeof(Slot))) / 4;
  static constexpr size_t kUsableSize = MapSizeBytes - kTotalMetadataBytes;
  static constexpr size_t kSlotSize = sizeof(Slot);
};
} // namespace di

#include "packed_map.cc"
#endif // DATABASE_INTERNAL_PACKED_MAP_H
