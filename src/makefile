# Compiler
CC = gcc
CFLAGS = -g -Wall

# Directories
TARGET_DIR = build

# Source and Object Files
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(TARGET_DIR)/%.o, $(SRCS))

# Output Executable
TARGET = main

# Default target
main: compile link
	@echo "Build complete."

# Compile each .c to .o
$(TARGET_DIR)/%.o: %.c
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile all source files
compile:
	@echo "Compiling source files..."
	$(MAKE) $(OBJS)

# Link object files
link:
	$(CC) $(CFLAGS) -o $(TARGET_DIR)/$(TARGET) $(OBJS)

# Clean build directory
clean:
	rm -rf $(TARGET_DIR)
	rm -f $(TARGET)
