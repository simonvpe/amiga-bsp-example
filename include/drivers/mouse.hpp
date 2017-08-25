#pragma once
#include "modules/chipset.hpp"

inline bool mouse_clicked(auto bsp) {
  return !bit_test<6, bsp.ciaa[CIA::Register::PRA]>();
}
