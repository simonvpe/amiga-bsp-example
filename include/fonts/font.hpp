#pragma once

extern volatile const uint8_t* __font_start;
extern volatile const uint8_t* __font_end;

struct font_t {
  font_t()
  : data{__font_start}
  , size{__font_end - __font_start}
  { }
  // offset is a table for telling where each character starts, each
  // character is 4 bytes wide and 25 lines high, and there are 10 chars per line
  // thus the chars o charline 1 starts at 0, 4, 8 etc bytes
  // on charline 2, we get an additional offset of 40*25 = 1000
  // (40 bytes per line * 25 lines high)
  // then the next charline is 1000*2 = 2000 etc
  // NOTICE! These values depend on the charset used!
  static constexpr uint16_t offset[60] {
       0,   4,   8,  12,  16,  20,  24,  28,  32,  36,
    1000,1004,1008,1012,1016,1020,1024,1028,1032,1036,
    2000,2004,2008,2012,2016,2020,2024,2028,2032,2036,
    3000,3004,3008,3012,3016,3020,3024,3028,3032,3036,    
    4000,4004,4008,4012,4016,4020,4024,4028,4032,4036,
    5000,5004,5008,5012,5016,5020,5024,5028,5032,5036
  };
  static constexpr uint8_t width  = 4;
  static constexpr uint8_t height = 25;
  volatile const uint8_t* data;
  const int size;
};

