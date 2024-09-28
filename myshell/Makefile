# Makefile
CC = gcc
TARGET = myshell
OBJS = cd_func.o newshell.o echo_getenv.o non_pipe_fork.o pipe_fork.o

CFLAGS = -Wall
LDFLAGS = 

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean : 
	rm -f $(OBJS)