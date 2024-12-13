#include "random.h"
#ifdef UBUNTU
#include <bsd/stdlib.h>
#else
#include <stdlib.h>
#endif

inline uint32_t get_random_unsigned_number(){
    return arc4random();
}

uint32_t get_random_unsigned_number_range(uint32_t min, uint32_t max){
    if (min >= max) return min;
    return arc4random_uniform(max - min) + min;
}


