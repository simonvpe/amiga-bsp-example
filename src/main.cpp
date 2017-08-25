#include "a500.hpp"

using cmap::make_map;
using cmap::map;
using cmap::lookup;

int main() {
  constexpr auto ciaa_pra         = bsp.ciaa[CIA::Register::PRA];
  constexpr auto chipset_vhposr   = bsp.chipset[Chipset::Register::VHPOSR];
  constexpr auto chipset_color00  = bsp.chipset[Chipset::Register::COLOR00];

  enum class Direction { Up, Down };
  
  uint8_t y = 0x40;
  Direction dir = Direction::Down;
  
  while(bit_test<6, ciaa_pra>()) {
    while(0xff != read_b<chipset_vhposr>())
      ; // Wait until vblank (ish)

    y += dir == Direction::Down ? 1 : -1;

    if(y >= 0xf0) dir = Direction::Up;
    if(y <= 0x50) dir = Direction::Down;
    
    while(y != read_b<chipset_vhposr>())
      ; // Wait for raster position to reach y

    write_w<chipset_color00>(0xfff);

    while(y == read_b<chipset_vhposr>())
      ; // Wait for raster position to pass y

    write_w<chipset_color00>(0x126);
  }

  return 0;
}
	   
