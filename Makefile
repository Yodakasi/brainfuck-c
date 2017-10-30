brainfuck: brainfuck.c
	gcc -Wall brainfuck.c -o brainfuck

clean:
	rm brainfuck

tests: brainfuck
	./brainfuck -f fibonacci.bf
	./brainfuck -f factorial.bf
