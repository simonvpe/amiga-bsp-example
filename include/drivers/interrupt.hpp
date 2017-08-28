#pragma once
#include "modules/chipset.hpp"


void disable_interrupts(auto bsp) {
  write_w<bsp.chipset[Chipset::Register::INTENA]>(0x7fff);
}
