brainfuck: brainfuck.c
	gcc -Wall brainfuck.c -o brainfuck

clean:
	rm brainfuck

tests: brainfuck
	./brainfuck -f ./test_cases/fizz_buzz.bf
	./brainfuck -f ./test_cases/sierpinski.bf
