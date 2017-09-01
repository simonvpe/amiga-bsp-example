#include <inttypes.h>

void* memcpy(void* dest, const void* src, uint32_t count) {
  uint8_t*       p_dest = (uint8_t*)dest;
  const uint8_t* p_src  = (uint8_t*)src;
  for(uint32_t i = 0 ; i < count ; ++i) *p_dest[i] = *p_src[i];
  return dest;
}
