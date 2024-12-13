CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -O2
SRC_DIR := src
LIB_DIR := lib
BUILD_DIR := build

DISTRO := $(shell . /etc/os-release && echo $$ID)

ifeq ($(DISTRO),ubuntu)
    CFLAGS += -DUBUNTU
    LDFLAGS += -lbsd
endif

# Find all .c files in SRC_DIR and LIB_DIR
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
LIB_FILES := $(wildcard $(LIB_DIR)/*.c)

# Create object file paths
SRC_OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
LIB_OBJECTS := $(patsubst $(LIB_DIR)/%.c, $(BUILD_DIR)/%.o, $(LIB_FILES))

# Executable targets for each source file in SRC_DIR
TARGETS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%, $(SRC_FILES))

.PHONY: all clean tests

all: $(TARGETS)

# Rule to build each executable from SRC_DIR
$(BUILD_DIR)/%: $(BUILD_DIR)/%.o $(LIB_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile library files into object files
$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

tests:
	./tests/generand.sh
