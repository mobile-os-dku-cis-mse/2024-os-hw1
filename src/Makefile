CC = /usr/bin/gcc
CFLAGS = -fdiagnostics-color=always -g
TARGET = SiSH
SRC = SiSH.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)