# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Iinclude -O2
LDFLAGS = -lraylib -lm -ldl -lpthread -lGL

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN = game

# Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(BIN)

# Link the final binary
$(BIN): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN)

# Phony targets
.PHONY: all clean
