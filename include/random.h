#ifndef ALONUTILS_RANDOM_H
#define ALONUTILS_RANDOM_H
#include <stdint.h>

uint32_t get_random_unsigned_number(void);

uint32_t get_random_unsigned_number_range(uint32_t min, uint32_t max);

uint64_t get_random_unsigned_64bit_number(void);

uint16_t get_random_unsigned_16bit_number(void);

#endif
