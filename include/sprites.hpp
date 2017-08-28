#pragma once
#include <array>
#include <utility>
#include <inttypes.h>

template<int height>
struct sprite_type {
  using row = std::pair<uint16_t, uint16_t>;
  using box = std::array<row,height>;
  
  uint8_t      vstart;
  uint8_t      hstart;
  uint8_t      vstop;
  uint8_t      empty;
  box          sprite_data;
  sprite_type* next;
};
