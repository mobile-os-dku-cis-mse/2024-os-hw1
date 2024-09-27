CC = gcc
TARGET = a.out
OBJECTS = SiSH.c

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $^

clean :
	rm a.out

# make
# make clean