#pragma once
#include <cstddef>
#include <variant>

enum class Access { R, W, S };

struct reg {
  constexpr reg(std::size_t address, std::size_t width, Access access)
  : address{address}
  , width{width}
  , access{access}
  { }

  const std::size_t address;
  const std::size_t width;
  const Access access;
};

inline uint8_t read_b(const reg& r)
{ return *reinterpret_cast<volatile const uint8_t*>(r.address); }

inline uint16_t read_w(const reg& r)
{ return *reinterpret_cast<volatile const uint16_t*>(r.address); }

inline uint32_t read_l(const reg& r)
{ return *reinterpret_cast<volatile const uint32_t*>(r.address); }

inline void write_b(const reg& r, uint8_t value)
{ *reinterpret_cast<volatile uint8_t*>(r.address) = value; }

inline void write_w(const reg& r, uint16_t value)
{ *reinterpret_cast<volatile uint16_t*>(r.address) = value; }

inline void write_l(const reg& r, uint32_t value)
{ *reinterpret_cast<volatile uint32_t*>(r.address) = value; }

template<int bit>
constexpr inline bool btst_b(const reg& r)
{
  return read_b(r) & bit;
};
