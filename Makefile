CC = gcc 
CFLAGS = -Wall -g 

TARGET = build/SiSH
BUILD_DIR = build 
OBJS = $(SRCS:%.c=build/%.o) 
	

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean: 
	rm -rf $(BUILD_DIR)
