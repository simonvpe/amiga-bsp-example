#include "a500.hpp"

using cmap::make_map;
using cmap::map;
using cmap::lookup;

int main() {
  constexpr auto ciaa_pra = lookup(bsp.ciab, CIA::Register::PRA);
  write_b(ciaa_pra, 0x12);
  return btst_b<6>(ciaa_pra);
}
	   
