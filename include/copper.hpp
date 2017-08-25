#include <inttypes.h>

namespace Copper {

using copper_instruction_type = uint32_t;

struct reg { const uint16_t address; };

struct mv {

  constexpr mv(uint16_t address, uint16_t value)
  : data{(address << 16) | value}
  { }

  constexpr mv(const reg& r, uint16_t value) 
  : data{(r.address << 16) | value}
  { }

  constexpr operator uint32_t() const 
  { return data; }

  const copper_instruction_type data;
};

#pragma GCC push_options
#pragma GCC optimize ("O0")
static volatile copper_instruction_type copperlist[] = {
  mv{reg{12},2},
  mv{reg{15},9}
};
#pragma GCC pop_options

auto reg_copperlist(const volatile copper_instruction_type& cl) {
  return cl;
}

void foo() {
  reg_copperlist(*copperlist);
}
};
