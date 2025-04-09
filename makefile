

CC=gcc
CFLAGS=-g -Wall -Wextra
LIBS=-lraylib -lxml2 -lfluidsynth
INCLUDE=-Ilib

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin


SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET=$(BIN_DIR)/toa


all:$(TARGET)


$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ) $(LIBS) $(INCLUDE) -o $@


$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LIBS) $(INCLUDE) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)/%.o $(TARGET) $(BUILD_DIR) $(BIN_DIR)

rebuild: clean all

