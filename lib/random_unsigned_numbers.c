#include "random.h"
#ifdef UBUNTU
#include <bsd/stdlib.h>
#else
#include <stdlib.h>
#endif

inline uint32_t get_random_unsigned_number() { return arc4random(); }

uint32_t get_random_unsigned_number_range(uint32_t min, uint32_t max) {
  if (min >= max)
    return min;
  return arc4random_uniform(max - min) + min;
}

inline uint64_t get_random_unsigned_64bit_number() {
  uint64_t high = (uint64_t)get_random_unsigned_number()
                  << 32; // Shift left by 32 bits to place in the high part
  uint64_t low = get_random_unsigned_number(); // This will be the low part
  return high | low; // Combine high and low parts with bitwise OR
}

inline uint16_t get_random_unsigned_16bit_number() {
  uint32_t random32 = get_random_unsigned_number();
  return (uint16_t)(random32 & 0xFFFF); // Mask to keep only the lower 16 bits
}
