#include "a500.hpp"

using cmap::make_map;
using cmap::map;
using cmap::lookup;

int main() {
  constexpr auto ciaa_pra = lookup(bsp.ciab, CIA::Register::PRA);
  return bit_test<6, ciaa_pra>();
}
	   
