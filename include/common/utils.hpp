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

  uint8_t read_b() const
  { return *reinterpret_cast<volatile const uint8_t*>(address); }

  uint16_t read_w() const
  { return *reinterpret_cast<volatile const uint16_t*>(address); }

  uint32_t read_l() const
  { return *reinterpret_cast<volatile const uint32_t*>(address); }

  void write_b(uint8_t value) const
  { *reinterpret_cast<volatile uint8_t*>(address) = value; }

  void write_w(uint16_t value) const
  { *reinterpret_cast<volatile uint16_t*>(address) = value; }

  void write_l(uint32_t value) const
  { *reinterpret_cast<volatile uint32_t*>(address) = value; }

  bool btst_b(int bit) const
  { return read_b() & (1 << bit); }

  bool btst_w(int bit) const
  { return read_w() & (1 << bit); }

  bool btst_l(int bit) const
  { return read_l() & (1 << bit); }
  
  
  const std::size_t address;
  const std::size_t width;
  const Access access;
};
