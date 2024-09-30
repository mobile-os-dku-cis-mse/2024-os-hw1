CC = gcc
CFLAGS = -Wall -g
TARGET = sish

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/command.c $(SRC_DIR)/input.c $(SRC_DIR)/path.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)