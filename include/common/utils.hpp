#include <cstddef>
#include <inttypes.h>
#include <stdexcept>

enum class Access : uint8_t { R, W, S };
enum class Width  : uint8_t { B, W, L };

/*
  This type encodes register information. In order to be able
  to pass it as non-type template arguments it needs to be
  serializable. To achieve this the address, width and access
  is packed into an uint32_t. To make this serialization transparent
  to the user there is also an implicit type cast into an uint32_t.
 */
struct reg {
  constexpr reg(uint16_t address, Width width, Access access)
  : data {
    uint32_t{0} 
    | (uint32_t{address} & 0xffff) 
    | ((static_cast<uint32_t>(width)  & 0xff) << 16) 
    | ((static_cast<uint32_t>(access) & 0xff) << 24)
  }
  { }

  constexpr reg(uint32_t data)
  : data{data}
  { }

  constexpr uint16_t address() const
  { return static_cast<uint16_t>(data & 0xffff); }

  constexpr Width width() const
  { return static_cast<Width>((data >> 16) & 0xff); }

  constexpr Access access() const
  { return static_cast<Access>((data >> 24) & 0xff); }

  constexpr operator uint32_t() const { return data; }

  const uint32_t data;
};

/*
  Reading from registers
 */

template<uint32_t reg_serialized>
inline uint8_t read_b() { 
  constexpr auto r = reg{reg_serialized};
  static_assert(r.width() == Width::B || r.width() == Width::W || r.width() == Width::L);
  return *reinterpret_cast<volatile const uint8_t*>(r.address()); 
}

template<uint32_t reg_serialized>
inline uint16_t read_w() { 
  constexpr auto r = reg{reg_serialized};
  static_assert(r.width() == Width::W || r.width() == Width::L);
  return *reinterpret_cast<volatile const uint16_t*>(r.address());
}

template<uint32_t reg_serialized>
inline uint32_t read_l() {
  constexpr auto r = reg{reg_serialized};
  static_assert(r.width() == Width::L);
  return *reinterpret_cast<volatile const uint32_t*>(r.address());
}

template<uint32_t reg_serialized>
inline void write_b(uint8_t value) {
  constexpr auto r = reg{reg_serialized};
  static_assert(r.width() == Width::B || r.width() == Width::W || r.width() == Width::L);
  *reinterpret_cast<volatile uint8_t*>(r.address()) = value;
}

template<uint32_t reg_serialized>
inline void write_w(uint16_t value) {
  constexpr auto r = reg{reg_serialized};
  static_assert(r.width() == Width::W || r.width() == Width::L);
  *reinterpret_cast<volatile uint16_t*>(r.address()) = value;
}

template<uint32_t reg_serialized>
inline void write_l(uint32_t value) {
  constexpr auto r = reg{reg_serialized};
  static_assert(r.width() == Width::L);
  *reinterpret_cast<volatile uint32_t*>(r.address()) = value;
}

template<int bit, uint32_t reg_serialized>
constexpr inline bool bit_test() {
  constexpr auto r = reg{reg_serialized};

  static_assert(bit >= 0);
  static_assert(r.access() == Access::R);
  
  if constexpr(r.width() == Width::B) {
    static_assert(bit < 8);
    return read_b<r>() & (1 << bit);
  }
  if constexpr(r.width() == Width::W) {
    static_assert(bit < 16);
    return read_w<r>() & (1 << bit);
  }
  if constexpr(r.width() == Width::L) {
    static_assert(bit < 32);
    return read_l<r>() & (1 << bit);
  }
}

auto foo() {
  constexpr auto r = reg{0xbeef, Width::B, Access::R};
  write_b<r>(55);
  return bit_test<7, r>();
}
