#include <uuid.h>

int main() {
  uuid_v4_t *uuid_v4 = generate_uuid();
  printf("%s", uuid_v4_to_string(uuid_v4));
  free(uuid_v4);
  return 0;
}
