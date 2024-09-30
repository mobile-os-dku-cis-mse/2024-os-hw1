CC = gcc
CFLAGS = -Wall

all: sish fork fork2 getenv stat

sish: sish.o
	$(CC) $(CFLAGS) -o sish sish.o

fork: fork.o
	$(CC) $(CFLAGS) -o fork fork.o

fork2: fork2.o
	$(CC) $(CFLAGS) -o fork2 fork2.o

getenv: getenv.o
	$(CC) $(CFLAGS) -o getenv getenv.o

stat: stat.o
	$(CC) $(CFLAGS) -o stat stat.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o sish fork fork2 getenv stat
