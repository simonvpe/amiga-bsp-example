#include "a500.hpp"

using cmap::make_map;
using cmap::map;
using cmap::lookup;

int main() {
  const auto ciaa_pra = lookup(bsp.ciab, CIA::Register::PRA);
  ciaa_pra.write_b(0x12);
  return ciaa_pra.btst_b(6);
}
	   
