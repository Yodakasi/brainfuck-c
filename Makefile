OBJS = src/brainfuck.c
CC = gcc
COMPILER_FLAGS = -Wall -Wextra
OBJ_NAME = bin/main

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)

test:
	./$(OBJ_NAME) -f ./test_cases/sierpinski.bf
