CC = gcc
CFLAGS = -g -Wall -I./src/header -I./src/c

SRC_DIR = src
SUBSRC_DIR = $(SRC_DIR)/c
BUILD_DIR = build

# Source files: main.c di src dan semua .c di src/c
SRCS = $(SRC_DIR)/main.c $(wildcard $(SUBSRC_DIR)/*.c)

# Object files di build/, path disesuaikan dari src/
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
OBJS := $(patsubst $(SUBSRC_DIR)/%.c,$(BUILD_DIR)/c/%.o,$(OBJS))

TARGET = $(BUILD_DIR)/main

# Target default, build executable
main: 
	@echo "Compiling the project..."
	@$(MAKE) compile
	@echo "Linking object files..."
	@$(MAKE) link
	@echo "Build complete."

# Compile semua .c jadi .o di build/
compile: $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/c/%.o: $(SUBSRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link semua objek jadi executable di build/main
link:
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Clean tetap sama seperti kamu minta
clean:
	rm -rf build
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
