#include <inttypes.h>

namespace copper {
  
template<uint32_t reg_serialized>
struct move_l {
  constexpr static auto r = reg{reg_serialized};
  static_assert(r.access() == Access::W);
  static_assert(r.width() == Width::L);
    
  move_l(const volatile void* ptr)
  : dst_hi(r.address() & 0x01FE)
  , val_hi((reinterpret_cast<uint32_t>(ptr) >> 16) & 0xFFFF)
  , dst_lo((dst_hi + 2) & 0x01FE)
  , val_lo(reinterpret_cast<uint32_t>(ptr) & 0xFFFF)
  { }
    
  uint16_t dst_hi;
  uint16_t val_hi;
  uint16_t dst_lo;
  uint16_t val_lo;
};

struct exit {
  exit() : value0{0xFFFF}, value1{0xFFFE} {}
  uint16_t value0;
  uint16_t value1;
};
  
}
