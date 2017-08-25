#include <cstddef>
#include <inttypes.h>
#include <stdexcept>

enum class Access : uint8_t { R, W, S };

struct reg {
  constexpr reg(uint16_t address, uint8_t width, Access access)
  : data {
    uint32_t{0} 
    | (uint32_t{address} & 0xffff) 
    | (uint32_t{width} << 16) 
    | ((static_cast<uint32_t>(access) & 0xff) << 24)
  }
  { }

  constexpr reg(uint32_t data)
  : data{data}
  { }

  constexpr uint16_t address() const
  { return static_cast<uint16_t>(data & 0xffff); }

  constexpr uint8_t width() const
  { return static_cast<uint8_t>((data >> 16) & 0xff); }

  constexpr Access access() const
  { return static_cast<Access>((data >> 24) & 0xff); }

  constexpr operator uint32_t() const { return data; }

  const uint32_t data;
};

template<uint32_t data>
inline uint8_t read_b() { 
  constexpr auto r = reg{data};
  static_assert(r.width() <= 8);
  return *reinterpret_cast<volatile const uint8_t*>(r.address()); 
}

template<uint32_t data>
inline uint16_t read_w() { 
  constexpr auto r = reg{data};
  static_assert(r.width() <= 16);
  return *reinterpret_cast<volatile const uint16_t*>(r.address());
}

template<uint32_t data>
inline uint32_t read_l() {
  constexpr auto r = reg{data};
  static_assert(r.width() <= 32);
  return *reinterpret_cast<volatile const uint32_t*>(r.address());
}

template<uint32_t data>
inline void write_b(uint8_t value) {
  constexpr auto r = reg{data};
  static_assert(r.width() <= 8);
  *reinterpret_cast<volatile uint8_t*>(r.address()) = value;
}

template<uint32_t data>
inline void write_w(uint16_t value) {
  constexpr auto r = reg{data};
  static_assert(r.width() <= 16);
  *reinterpret_cast<volatile uint16_t*>(r.address()) = value;
}

template<uint32_t data>
inline void write_l(uint32_t value) {
  constexpr auto r = reg{data};
  static_assert(r.width() <= 32);
  *reinterpret_cast<volatile uint32_t*>(r.address()) = value;
}

template<int bit, uint32_t data>
constexpr inline bool bit_test() {

  constexpr auto r = reg{data};

  static_assert(bit >= 0);
  static_assert(bit < r.width());
  static_assert(r.access() == Access::R);

  if constexpr( r.width() <= 8 ) {
    return read_b<r>() & (1 << bit);
  }

  if constexpr( r.width() <= 16 ) {
    return read_w<r>() & (1 << bit);
  }

  return read_l<r>() & (1 << bit);
}

auto foo() {
  constexpr auto r = reg{0xbeef, 8, Access::R};
  write_b<r>(55);
  return bit_test<7, r>();
}
