# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Isrc -Isrc/utils -Iinclude

# Output file
TARGET = ED.exe

# Directories
SRC_DIR = src

# Source and object files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Raylib and Windows libs
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Default build
all: $(TARGET)

# Link
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

# Compile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
