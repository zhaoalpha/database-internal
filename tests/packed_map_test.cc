//
// Created by zhao on 23-4-26.
//

#include "../src/utils/packed_map.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

template <uint16_t Size> class PackedMapTest {
public:
  PackedMapTest() = default;
  PackedMapTest(const std::string &lower, const std::string &upper)
      : map_(reinterpret_cast<const uint8_t *>(lower.data()), lower.size(),
             reinterpret_cast<const uint8_t *>(upper.data()), upper.size()) {}
  uint16_t ShowLowerKeyOffset() { return map_.ShowLowerKeyOffset(); }

private:
  di::PackedMap<Size> map_;
};

TEST(PackedMapTest, SampleTest) {
  const std::string lower = "aaaaa";
  const std::string upper = "aaazz";
  auto test = lower.data();
  std::cout << "test: " <<test << std::endl;
  //  di::PackedMap<uint16_t(4096)> map(
  //      reinterpret_cast<const uint8_t *>(lower.data()), lower.size(),
  //      reinterpret_cast<const uint8_t *>(upper.data()), upper.size());
  //  auto lower_key_offset = map.ShowLowerKeyOffset();
  //  EXPECT_EQ(uint16_t(4096), lower_key_offset);
}