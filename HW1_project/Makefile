CC = gcc

CFLAGS = -Wall

TARGET = app

SRCS = main.c functions.c

OBJS = main.o functions.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	rm *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET)
