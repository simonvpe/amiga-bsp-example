#pragma once
#include "cmap.hpp"
#include "utils.hpp"

namespace CIA {
  using cmap::map;
  using cmap::make_map;
  
  enum class Register {
    PRA, PRB, DDRA, DDRB, TALO, TALHI, TBLO, TBHI,
    TODLO, TODMID, TODHI, SDR, ICR, CRA, CRB
  };

  constexpr auto ciaa = make_map(
      map(Register::PRA,    reg{0xBFE001, 8, Access::R}),
      map(Register::PRB,    reg{0xBFE101, 8, Access::R}),
      map(Register::DDRA,   reg{0xBFE201, 8, Access::R}),
      map(Register::DDRB,   reg{0xBFE301, 8, Access::R}),
      map(Register::TALO,   reg{0xBFE401, 8, Access::R}),
      map(Register::TALHI,  reg{0xBFE501, 8, Access::R}),
      map(Register::TBLO,   reg{0xBFE601, 8, Access::R}),
      map(Register::TBHI,   reg{0xBFE701, 8, Access::R}),
      map(Register::TODLO,  reg{0xBFE801, 8, Access::R}),
      map(Register::TODMID, reg{0xBFE901, 8, Access::R}),
      map(Register::TODHI,  reg{0xBFEA01, 8, Access::R}),
      map(Register::SDR,    reg{0xBFEC01, 8, Access::R}),
      map(Register::ICR,    reg{0xBFED01, 8, Access::R}),
      map(Register::CRA,    reg{0xBFEE01, 8, Access::R}),
      map(Register::CRB,    reg{0xBFEF01, 8, Access::R})
  );

  constexpr auto ciab = make_map(
      map(Register::PRA,    reg{0xBFD000, 8, Access::R}),
      map(Register::PRB,    reg{0xBFD100, 8, Access::R}),
      map(Register::DDRA,   reg{0xBFD200, 8, Access::R}),
      map(Register::DDRB,   reg{0xBFD300, 8, Access::R}),
      map(Register::TALO,   reg{0xBFD400, 8, Access::R}),
      map(Register::TALHI,  reg{0xBFD500, 8, Access::R}),
      map(Register::TBLO,   reg{0xBFD600, 8, Access::R}),
      map(Register::TBHI,   reg{0xBFD700, 8, Access::R}),
      map(Register::TODLO,  reg{0xBFD800, 8, Access::R}),
      map(Register::TODMID, reg{0xBFD900, 8, Access::R}),
      map(Register::TODHI,  reg{0xBFDA00, 8, Access::R}),
      map(Register::SDR,    reg{0xBFDC00, 8, Access::R}),
      map(Register::ICR,    reg{0xBFDD00, 8, Access::R}),
      map(Register::CRA,    reg{0xBFDE00, 8, Access::R}),
      map(Register::CRB,    reg{0xBFDF00, 8, Access::R})
  );
};
