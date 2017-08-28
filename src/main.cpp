#include "a500.hpp"
#include "drivers/mouse.hpp"
#include "drivers/palette.hpp"
#include "drivers/interrupt.hpp"

#include <tuple>
#include <algorithm>

using cmap::make_map;
using cmap::map;
using cmap::lookup;

enum class Direction { Up, Down };
constexpr inline auto advance_bar(auto bsp, Direction dir, uint8_t pos) {
  constexpr auto upper_limit = uint8_t{0xf0};
  constexpr auto lower_limit = uint8_t{0x50};
  pos += (dir == Direction::Down ? 1 : -1);
  dir = pos > upper_limit ? Direction::Up : pos < lower_limit ? Direction::Down : dir;
  return std::make_tuple(dir, pos);
}

constexpr inline void wait_raster(auto bsp, auto pos) {
  while(pos != read_b<bsp.chipset[Chipset::Register::VHPOSR]>())
    ;
}

constexpr inline void wait_not_raster(auto bsp, auto pos) {
  while(pos == read_b<bsp.chipset[Chipset::Register::VHPOSR]>())
    ;
}

int main() {
  
  uint8_t y = 0x40;
  Direction dir = Direction::Down;

  while(!mouse_clicked(bsp)) {
    wait_raster(bsp, 0x2c);
    set_color<Color::C00>(bsp, {0,0,0});
    std::tie(dir, y) = advance_bar(bsp, dir, y);
    wait_raster(bsp, y);
    set_color<Color::C00>(bsp, {0,0,15});
    wait_not_raster(bsp, y);
    set_color<Color::C00>(bsp, {1,2,6});
  }
  return 0;
}
	   
