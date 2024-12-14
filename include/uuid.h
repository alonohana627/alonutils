#ifndef ALONUTILS_UUID_H
#define ALONUTILS_UUID_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// UUID v4
// It is not the fastest UUID v4 generator, in fact it is slow as hell.
// But this implementation is meant for understanding UUID v4, being decently
// structured, and as a study project

/*
0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                           random_a                            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|          random_a             |  ver  |       random_b        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|var|                       random_c                            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                           random_c                            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

typedef struct uuid_v4 {
  uint64_t random_a : 48;
  uint8_t ver : 4;
  uint16_t random_b : 12;
  uint8_t var : 2;
  uint64_t random_c : 62;
} uuid_v4_t;

uint64_t generate_random_a(void);

uint8_t get_uuid_v4_version(void);

uint16_t generate_random_b(void);

uint8_t get_uuid_v4_variant(void);

uint64_t generate_random_c(void);

uuid_v4_t *generate_uuid(void);

const char *uuid_v4_to_string(uuid_v4_t *uuid);

char *fast_uuid_v4(void);

#endif
