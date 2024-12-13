#include "random.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void usage(void) {
    printf("generand\n");
    printf("generand --help\n");
    printf("generand --min <min> --max <max>\n");
    printf("===================\n");
    printf("Error codes:\n");
    printf("0: success\n");
    printf("1: unknown argument\n");
    printf("2: usage\n");
    printf("3: min must be less than max\n");
}

typedef struct generand_options {
    uint32_t min;
    uint32_t max;
} generand_options;

generand_options get_options(int argc, char **argv) {
    uint32_t min = 0;
    uint32_t max = 100;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--min", sizeof("--min")) == 0 && i + 1 < argc) {
            min = (uint32_t) strtoul(argv[++i], NULL, 10);
        } else if (strncmp(argv[i], "--max", sizeof("--max")) == 0 && i + 1 < argc) {
            max = (uint32_t) strtoul(argv[++i], NULL, 10);
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            usage();
            exit(2);
        }
    }

    generand_options options = {
            .min = min,
            .max = max
    };
    return options;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("%u", get_random_unsigned_number());
        return 0;
    } else if (argc == 2) {
        if (strncmp(argv[1], "--help", sizeof("--help"))) {
            usage();
            exit(1); // prevents the program from accidentally including its result in a pipe
        }
    }

    generand_options options = get_options(argc, argv);

    if (options.min >= options.max) {
        printf("min must be less than max\n");
        return 3;
    }

    printf("%u", get_random_unsigned_number_range(options.min, options.max));
    return 0;
}
