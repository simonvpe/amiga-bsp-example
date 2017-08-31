#pragma once

extern const uint8_t* __font_start;
extern const uint8_t* __font_end;

struct font_t {
  font_t()
  : data{__font_start}
  , size{__font_end - __font_start}
  { }
  volatile const uint8_t* data;
  const int size;
};

