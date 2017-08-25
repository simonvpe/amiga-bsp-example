#pragma once
#include "cia.hpp"
#include "chipset.hpp"

constexpr struct a500_bsp {
  static constexpr auto ciaa = CIA::ciaa;
  static constexpr auto ciab = CIA::ciab;
  static constexpr auto chipset = Chipset::ocs;
} bsp;

