#pragma once
#include <array>
#include "common/prng.hpp"

template<int N, int vstart, int vstop>
struct star_sprite_t {
  static_assert(N >= 4);
  static_assert(N % 4 == 0);
  static_assert((vstop - vstart)/N > 0);
  static_assert(vstart >  0x00);
  static_assert(vstart <= 0xFF);
  static_assert(vstop >   0x00);
  static_assert(vstop <=  0xFF);

  static constexpr auto groups = N/4;
  static constexpr auto y_separation = (vstop - vstart) / N;
  static constexpr uint8_t  speed[]   = {3,     1,     2,     1};
  static constexpr uint16_t pixels0[] = {0x8000,0x8000,0x0000,0x8000};
  static constexpr uint16_t pixels1[] = {0x8000,0x0000,0x8000,0x0000};
  
  struct sprite_t {
    uint8_t y0;
    uint8_t x0;
    uint8_t y1;
    uint8_t control;
    uint16_t pixels[2];
  };
  
  star_sprite_t() {
    
    uint8_t x0 = 0;
    uint8_t y0 = vstart;
    
    for(auto& group : data) {
      auto const * p_pixels0 = pixels0;
      auto const * p_pixels1 = pixels1;

      for(auto& sprite : group) {
	x0 += rng.next();
	y0 += y_separation;
	sprite.y0 = y0;
	sprite.x0 = x0;
	sprite.y1 = sprite.y0 + 1;
	sprite.control = 0;
	sprite.pixels[0] = *p_pixels0++;
	sprite.pixels[1] = *p_pixels1++;
      }
    }
    end_data[0] = 0;
    end_data[1] = 0;
  }
  
  void tick() {
    for(auto& group : data) {
      uint8_t i = 0;
      for(auto& sprite : group) {
	sprite.x0 += speed[i];
	++i;
      }
    }
  }
  
  std::array<std::array<sprite_t, 4>, groups> data;
  uint16_t end_data[2];
  prng_t rng;
};
