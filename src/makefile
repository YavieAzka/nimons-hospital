# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -I./src/header -I./src/c

# Source directories
SRC_DIR = ./src
SRC_C_DIR = ./src/c

# Build directory
BUILD_DIR = ./build

# Source files in src and src/c
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_C_DIR)/*.c)

# Object files will be in build/ directory, without subfolders
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

# Target executable
TARGET = $(BUILD_DIR)/main

# Default target
all: $(TARGET)
	@echo "Build finished."

# Link step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile step for files in src/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile step for files in src/c/
$(BUILD_DIR)/%.o: $(SRC_C_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf build
	rm -f main
	rm -f *.o *.out *.exe *.a *.so *.dll *.dSYM *.pdb *.ilk *.idb *.lib *.exp
