#include "random.h"
#include "uuid.h"
#include <ctype.h>

uint64_t generate_random_a(void) {
  uint64_t num = get_random_unsigned_64bit_number();
  return num >> 16; // Takes the first 48 bits only
}

uint8_t get_uuid_v4_version() {
  return 0b0100; // return 4;
}

uint16_t generate_random_b(void) {
  uint16_t num = get_random_unsigned_16bit_number();
  return num >> 4; // Takes the first 12 bits only
}

uint8_t get_uuid_v4_variant() {
  return 0b10; // Setting variant to 10xxxxxx per RFC 4122
}

uint64_t generate_random_c(void) {
  uint64_t num = get_random_unsigned_64bit_number();
  return num;
}

uuid_v4_t *generate_uuid(void) {
  uuid_v4_t *uuid_v4 = malloc(sizeof(uuid_v4_t));
  if (uuid_v4 == NULL) {
    fprintf(stderr, "Error: malloc failed\n");
    exit(100);
  }

  uuid_v4->random_a = generate_random_a();
  uuid_v4->ver = get_uuid_v4_version();
  uuid_v4->random_b = generate_random_b();
  uuid_v4->var = get_uuid_v4_variant();
  uuid_v4->random_c = generate_random_c();

  return uuid_v4;
}

const char *uuid_v4_to_string(uuid_v4_t *uuid) {
  static char uuid_str[37];       // 36 characters + null terminator
  static char lowercase_uuid[37]; // 36 characters + null terminator

  uint32_t first_part = (uint32_t)(uuid->random_a >> 16);
  uint16_t second_part = (uint16_t)(uuid->random_a & 0xFFFF);
  uint16_t third_part = (uuid->ver << 12) | (uuid->random_b & 0x0FFF);
  uint16_t fourth_part_high =
      (uuid->var << 14) | (uint16_t)((uuid->random_c >> 48) & 0x3FFF);
  uint64_t fourth_part_low = uuid->random_c & 0xFFFFFFFFFFFF;

  snprintf(uuid_str, sizeof(uuid_str), "%08X-%04X-%04X-%04X-%012lX", first_part,
           second_part, third_part, fourth_part_high, fourth_part_low);

  // Converts the str to lowercase
  for (int i = 0; i < 36; i++) {
    lowercase_uuid[i] = tolower(uuid_str[i]);
  }

  return lowercase_uuid;
}

char *fast_uuid_v4(void) {
  const char *hex = "0123456789abcdef";
  char *uuid = (char *)malloc(
      37 * sizeof(char)); // Allocate memory for 36 characters + null terminator
  if (!uuid) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 36; i++) {
    if (i == 8 || i == 13 || i == 18 || i == 23) {
      uuid[i] = '-';
    } else if (i == 14) {
      uuid[i] = '4'; // UUID version 4
    } else if (i == 19) {
      uuid[i] = hex[(arc4random() % 4) + 8]; // UUID variant
    } else {
      uuid[i] = hex[arc4random() % 16];
    }
  }

  uuid[36] = '\0'; // Null-terminate the string
  return uuid;
}
