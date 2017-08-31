#pragma once

struct dummy_sprite_t {
  dummy_sprite_t() {
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
  }
  volatile uint32_t data[4];
};
