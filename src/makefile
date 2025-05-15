CC = gcc
CFLAGS = -g -Wall -I./src/header -I./src/c

SRC_DIR = src
SUBSRC_DIR = $(SRC_DIR)/c
BUILD_DIR = build

# Semua source file main.c dan .c di src/c
SRCS = $(SRC_DIR)/main.c $(wildcard $(SUBSRC_DIR)/*.c)

# Semua object file di build/, path disesuaikan
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
OBJS := $(patsubst $(SUBSRC_DIR)/%.c, $(BUILD_DIR)/c/%.o, $(OBJS))

TARGET = $(BUILD_DIR)/main

.PHONY: main compile link clean

# Default target: compile + link
main:
	@echo "Compiling the project..."
	@$(MAKE) compile
	@echo "Linking object files..."
	@$(MAKE) link
	@echo "Build complete."

# Compile semua source file jadi object
compile: $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/c/%.o: $(SUBSRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link semua object file ke executable
link:
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Clean tetap sama
clean:
	rm -rf $(BUILD_DIR)
	rm -f main
	rm -f *.o
	rm -f *.out
	rm -f *.exe
	rm -f *.a
	rm -f *.so
	rm -f *.dll
	rm -f *.dSYM
	rm -f *.pdb
	rm -f *.ilk
	rm -f *.idb
	rm -f *.lib
	rm -f *.exp
