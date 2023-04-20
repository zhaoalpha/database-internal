//
// Created by zhao on 23-4-20.
//

#ifndef DATABASE_INTERNAL_PACKED_MAP_H
#define DATABASE_INTERNAL_PACKED_MAP_H
namespace di {
// PackedMap可以在编译期间进行配置，但是要严格小于64KB
// Key最大大小由kMaxKeySizeBytes指定
// 为了使用前缀编码，key的范围必须指定，所以要知道最大Key和最小的Key
// 提供8字节供存储溢出页的元信息
// 不是线程安全的需要外部进行互斥
#include <cstddef>
#include <cstdint>
// TODO 编译期确定大小利用模板实现？
template <uint16_t MapSizeBytes> class PackedMap {
public:
  struct Header {
    struct FenceKeySlot{
      uint16_t offset;
      uint16_t length;
    };
  };
  struct Slot{
    uint16_t offset;
    uint16_t key_length;
    // value length
    uint16_t payload_length;
    union {
      uint32_t head;
      uint8_t head_bytes[4];
    };
  };
  static constexpr size_t kMaxKeySizeBytes = 6;
};
} // namespace di
#endif // DATABASE_INTERNAL_PACKED_MAP_H
