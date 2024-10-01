CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lreadline
SRC = x.c          
OBJ = x.o         
TARGET = x         


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f *.o $(TARGET)
