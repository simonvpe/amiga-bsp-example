#pragma once

struct bitplane_t {
  static constexpr auto bytes = 8000U;
  bitplane_t() {
    for(auto i = 0 ; i < bytes/4 ; ++i)
      data[i] = 0xFFFFFFFF;
  }
  volatile uint32_t data[bytes/4];
};
