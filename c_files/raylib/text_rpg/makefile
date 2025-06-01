# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude -O2 -g
LDFLAGS = -lraylib -lm -ldl -lpthread -lGL

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN = game

# Files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(BIN)

# Link the final binary
$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN)

# Phony targets
.PHONY: all clean
