# Compiler
CC = gcc

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN = app

# Source files
SRCS = $(SRC_DIR)/main.c

# Output object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler and linker flags
CFLAGS = -Wall -std=c99
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Default target
all: $(BIN)

# Link
$(BIN): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run app
run: app
	./app


# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
