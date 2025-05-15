CC = gcc
CFLAGS = -g -Wall -I./header -I./c
SRC_DIR = .
SRC_C_DIR = ./c
BUILD_DIR = ./build
TARGET = main

# Semua file .c di src dan src/c
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_C_DIR)/*.c)

# Buat object file path di build (misal src/main.c -> build/main.o, src/c/diagnosis.c -> build/diagnosis.o)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
OBJS := $(patsubst $(SRC_C_DIR)/%.c, $(BUILD_DIR)/%.o, $(OBJS))

# Default target
all: $(TARGET)

# Link object files jadi executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^

# Compile source jadi object file di build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_C_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Bersihkan hasil build
clean:
	rm -rf $(BUILD_DIR)/*
