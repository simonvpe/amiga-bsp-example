#include <inttypes.h>

void* memset(void* ptr, int value, uint32_t num) {
  uint8_t* p = (uint8_t*)ptr;
  uint8_t  v = (uint8_t)value;
  while(num-- > 0) *p = v;
  return ptr;
}
