# Compiler dan flags
CC = gcc
CFLAGS = -g -Wall -I.

# Folder
SRC_DIR = src/c
BUILD_DIR = build

# Semua source files dan object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Target executable
TARGET = main

# Default target
all: $(TARGET)

# Linking objek-objek menjadi executable
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CC) $(CFLAGS) -o $@ $^

# Kompilasi tiap .c jadi .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Bersih-bersih file hasil build
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Opsional: run program
run: $(TARGET)
	./$(TARGET)
