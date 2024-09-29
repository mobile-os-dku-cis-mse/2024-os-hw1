CC = gcc
CFLAGS = -Wall -g
TARGET = SiSH
SRC = main.c shell.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
