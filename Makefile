# 컴파일러 설정
CC = gcc
CFLAGS = -Wall -g

# 디렉터리 설정
SRC_DIR = src
TOOLS_DIR = $(SRC_DIR)/tools
EXAMPLE_DIR = example

# 타겟 실행 파일
TARGET = my_program

# src 내 소스 파일 및 헤더 파일
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/instruction_parser.c \
            $(TOOLS_DIR)/stack.c $(TOOLS_DIR)/string_tools.c
OBJ_FILES = $(SRC_FILES:.c=.o)

# 기본 빌드 규칙 (src 디렉터리 내)
all: $(TARGET) example_targets

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# src 내 소스 파일들 컴파일 규칙
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# tools 디렉터리 내 소스 파일들 컴파일 규칙
$(TOOLS_DIR)/%.o: $(TOOLS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@



# 정리 규칙
clean:
	rm -f $(SRC_DIR)/*.o $(TOOLS_DIR)/*.o $(TARGET)


.PHONY: all clean 
