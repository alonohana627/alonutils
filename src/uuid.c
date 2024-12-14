#include <string.h>
#include <uuid.h>

void usage(void) {
  printf("uuid\n");
  printf("uuid --help\n");
  printf("uuid --version <number>\n");
  printf("===================\n");
  printf("Error codes:\n");
  printf("0: success\n");
  printf("1: unknown argument\n");
  printf("2: usage\n");
  printf("3: wrong version number\n");
}
typedef struct uuid_options {
  uint32_t version;
} uuid_options;

uuid_options get_options(int argc, char **argv) {
  uint32_t version = 4;
  for (int i = 1; i < argc; i++) {
    if (strncmp(argv[i], "--version", sizeof("--version")) == 0 &&
        i + 1 < argc) {
      version = (uint32_t)strtoul(argv[++i], NULL, 10);
    } else {
      fprintf(stderr, "Unknown argument: %s\n", argv[i]);
      usage();
      exit(1);
    }
  }

  uuid_options options = {.version = version};
  return options;
}

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("%s", uuid_v4_to_string(generate_uuid()));
    return 0;
  } else if (argc == 2) {
    if (strncmp(argv[1], "--help", sizeof("--help"))) {
      usage();
      exit(1);
    }
  }

  uuid_options options = get_options(argc, argv);
  switch (options.version) {
  case 4:
    printf("%s", uuid_v4_to_string(generate_uuid()));
    break;
  default:
    fprintf(stderr, "Unsupported version: %u\n", options.version);
    usage();
    exit(3);
  }
  return 0;
}
