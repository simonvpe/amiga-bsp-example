#include "a500.hpp"
#include "drivers/mouse.hpp"
#include "drivers/palette.hpp"
#include "drivers/interrupt.hpp"

using cmap::make_map;
using cmap::map;
using cmap::lookup;


int main() {
  constexpr auto chipset_vposr    = bsp.chipset[Chipset::Register::VPOSR];  
  constexpr auto chipset_vhposr   = bsp.chipset[Chipset::Register::VHPOSR];

  disable_interrupts(bsp);
  
  enum class Direction { Up, Down };
  
  uint8_t y = 0x40;
  Direction dir = Direction::Down;

  while(!mouse_clicked(bsp)) {
    
    while(bit_test<8,chipset_vposr>() || 0x2c != read_b<chipset_vhposr>())
      ; // Wait until vblank (ish)

    set_color<Color::C00>(bsp, {0,0,0});
    
    y += dir == Direction::Down ? 1 : -1;

    if(y >= 0xf0) dir = Direction::Up;
    if(y <= 0x50) dir = Direction::Down;
    
    while(y != read_b<chipset_vhposr>())
      ; // Wait for raster position to reach y

    set_color<Color::C00>(bsp, {0,0,15});

    while(y == read_b<chipset_vhposr>())
      ; // Wait for raster position to pass y

    set_color<Color::C00>(bsp, {1,2,6});
  }

  return 0;
}
	   
