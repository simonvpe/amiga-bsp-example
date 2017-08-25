#pragma once
#include "modules/chipset.hpp"

enum class Color {
  C00, C01, C02, C03, C04, C05, C06, C07,
  C08, C09, C10, C11, C12, C13, C14, C15,
  C16, C17, C18, C19, C20, C21, C22, C23,
  C24, C25, C26, C27, C28, C29, C30, C31
};

struct color_type {
  constexpr color_type(int8_t r, int8_t g, int8_t b)
  : data(static_cast<uint16_t>(r & 0xf) << 8
	 | static_cast<uint16_t>(g & 0xf) << 4
	 | static_cast<uint16_t>(b & 0xf))
  { }
  const uint16_t data;
};

template<Color idx>
void set_color(auto bsp, color_type color) {
  using cmap::make_lookup;
  using cmap::map;
  
  constexpr auto color_lookup = make_lookup(
    map(Color::C00, Chipset::Register::COLOR00),
    map(Color::C01, Chipset::Register::COLOR01),
    map(Color::C02, Chipset::Register::COLOR02),
    map(Color::C03, Chipset::Register::COLOR03),
    map(Color::C04, Chipset::Register::COLOR04),
    map(Color::C05, Chipset::Register::COLOR05),
    map(Color::C06, Chipset::Register::COLOR06),
    map(Color::C07, Chipset::Register::COLOR07),
    map(Color::C08, Chipset::Register::COLOR08),
    map(Color::C09, Chipset::Register::COLOR09),
    map(Color::C10, Chipset::Register::COLOR10),
    map(Color::C11, Chipset::Register::COLOR11),
    map(Color::C12, Chipset::Register::COLOR12),
    map(Color::C13, Chipset::Register::COLOR13),
    map(Color::C14, Chipset::Register::COLOR14),
    map(Color::C15, Chipset::Register::COLOR15),
    map(Color::C16, Chipset::Register::COLOR16),
    map(Color::C17, Chipset::Register::COLOR17),
    map(Color::C18, Chipset::Register::COLOR18),
    map(Color::C19, Chipset::Register::COLOR19),
    map(Color::C20, Chipset::Register::COLOR20),
    map(Color::C21, Chipset::Register::COLOR21),
    map(Color::C22, Chipset::Register::COLOR22),
    map(Color::C23, Chipset::Register::COLOR23),
    map(Color::C24, Chipset::Register::COLOR24),
    map(Color::C25, Chipset::Register::COLOR25),
    map(Color::C26, Chipset::Register::COLOR26),
    map(Color::C27, Chipset::Register::COLOR27),
    map(Color::C28, Chipset::Register::COLOR28),
    map(Color::C29, Chipset::Register::COLOR29),
    map(Color::C30, Chipset::Register::COLOR30),
    map(Color::C31, Chipset::Register::COLOR31)
  );

  write_w<bsp.chipset[color_lookup[idx]]>(color.data);
}
