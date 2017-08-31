#pragma once

struct prng_t {
  uint32_t state;
  
  prng_t()
  : state{0x9876fedc}
  { }

  uint32_t next() {
    state = state*0xffe + 0xdeadbeef;
    return state;
  }
};
