#pragma once
#include "cmap.hpp"
#include "common/utils.hpp"

namespace CIA {
  using cmap::map;
  using cmap::make_lookup;
  
  enum class Register {
    PRA, PRB, DDRA, DDRB, TALO, TALHI, TBLO, TBHI,
    TODLO, TODMID, TODHI, SDR, ICR, CRA, CRB
  };

  constexpr auto ciaa = make_lookup(
      map(Register::PRA,    reg{0xBFE001, Width::B, Access::R}),
      map(Register::PRB,    reg{0xBFE101, Width::B, Access::R}),
      map(Register::DDRA,   reg{0xBFE201, Width::B, Access::R}),
      map(Register::DDRB,   reg{0xBFE301, Width::B, Access::R}),
      map(Register::TALO,   reg{0xBFE401, Width::B, Access::R}),
      map(Register::TALHI,  reg{0xBFE501, Width::B, Access::R}),
      map(Register::TBLO,   reg{0xBFE601, Width::B, Access::R}),
      map(Register::TBHI,   reg{0xBFE701, Width::B, Access::R}),
      map(Register::TODLO,  reg{0xBFE801, Width::B, Access::R}),
      map(Register::TODMID, reg{0xBFE901, Width::B, Access::R}),
      map(Register::TODHI,  reg{0xBFEA01, Width::B, Access::R}),
      map(Register::SDR,    reg{0xBFEC01, Width::B, Access::R}),
      map(Register::ICR,    reg{0xBFED01, Width::B, Access::R}),
      map(Register::CRA,    reg{0xBFEE01, Width::B, Access::R}),
      map(Register::CRB,    reg{0xBFEF01, Width::B, Access::R})
  );

  constexpr auto ciab = make_lookup(
      map(Register::PRA,    reg{0xBFD000, Width::B, Access::R}),
      map(Register::PRB,    reg{0xBFD100, Width::B, Access::R}),
      map(Register::DDRA,   reg{0xBFD200, Width::B, Access::R}),
      map(Register::DDRB,   reg{0xBFD300, Width::B, Access::R}),
      map(Register::TALO,   reg{0xBFD400, Width::B, Access::R}),
      map(Register::TALHI,  reg{0xBFD500, Width::B, Access::R}),
      map(Register::TBLO,   reg{0xBFD600, Width::B, Access::R}),
      map(Register::TBHI,   reg{0xBFD700, Width::B, Access::R}),
      map(Register::TODLO,  reg{0xBFD800, Width::B, Access::R}),
      map(Register::TODMID, reg{0xBFD900, Width::B, Access::R}),
      map(Register::TODHI,  reg{0xBFDA00, Width::B, Access::R}),
      map(Register::SDR,    reg{0xBFDC00, Width::B, Access::R}),
      map(Register::ICR,    reg{0xBFDD00, Width::B, Access::R}),
      map(Register::CRA,    reg{0xBFDE00, Width::B, Access::R}),
      map(Register::CRB,    reg{0xBFDF00, Width::B, Access::R})
  );
};
