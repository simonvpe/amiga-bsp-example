#include "a500.hpp"

using cmap::make_map;
using cmap::map;
using cmap::lookup;

int main() {
  constexpr auto ciaa_pra         = bsp.ciaa[CIA::Register::PRA];
  constexpr auto chipset_vhposr   = bsp.chipset[Chipset::Register::VHPOSR];
  constexpr auto chipset_color00  = bsp.chipset[Chipset::Register::COLOR00];

  while(bit_test<6, ciaa_pra>()) {
    while(0xAC != read_b<chipset_vhposr>())
      ; // Wait for raster position

    write_w<chipset_color00>(0xfff);

    while(0xAC == read_b<chipset_vhposr>())
      ;

    write_w<chipset_color00>(0x126);
  }

  return 0;
}
	   
