#pragma once
#include "modules/cia.hpp"
#include "modules/chipset.hpp"

constexpr struct a500_bsp {
  static constexpr auto ciaa = CIA::ciaa;
  static constexpr auto ciab = CIA::ciab;
  static constexpr auto chipset = Chipset::ocs;
} bsp;

