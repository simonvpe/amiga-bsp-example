#include "a500.hpp"

using cmap::make_map;
using cmap::map;
using cmap::lookup;

int main() {
  constexpr auto ciaa_pra = lookup(bsp.ciaa, CIA::Register::PRA);
  while(bit_test<6, ciaa_pra>())
    ;
  return 0;
}
	   
