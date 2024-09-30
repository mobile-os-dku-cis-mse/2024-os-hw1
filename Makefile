CC=gcc

all: sish explore devproc fedit

sish: sish.c
	$(CC) sish.c -o sish

explore: explore.c
	$(CC) explore.c -o explore

devproc: devproc.c
	$(CC) devproc.c -o devproc

fedit: fedit.c
	$(CC) fedit.c -o fedit

clean:
	rm -f sish explore devproc fedit

run: sish
	./sish
