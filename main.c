#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*

    >   Move the pointer to the right
    <   Move the pointer to the left
    +   Increment the memory cell under the pointer
    -   Decrement the memory cell under the pointer
    .   Output the character signified by the cell at the pointer
    ,   Input a character and store it in the cell at the pointer
    [   Jump past the matching ] if the cell under the pointer is 0
    ]   Jump back to the matching [ if the cell under the pointer is nonzero

    TODO
    - compiler
    - error handling
    - better code

*/

char *file_name;
extern int errno;

char *load_code() {
    size_t length;
    char *buffer = 0;
    FILE *source_code = fopen(file_name, "rb");

    if (source_code) {
        fseek(source_code, 0, SEEK_END);
        length = ftell(source_code);
        fseek(source_code, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread (buffer, 1, length, source_code);
        }
    fclose (source_code);
    }

    else {
            perror("Error while opening file: ");
            exit(EXIT_FAILURE);

    }

    return buffer;
}

int bf_interpreter(char source[], size_t memory_size) {
    char memory[memory_size];
    memset(memory, 0, memory_size);
    char *pointer = memory;
    char instruction;
    size_t loop_counter;

    for (int i = 0; source[i] != '\0'; i++) {
        instruction = source[i];
        switch (instruction) {
            case '+':
                ++*pointer;
                break;
            case '-':
                --*pointer;
                break;
            case '>':
                ++pointer;
                break;
            case '<':
                --pointer;
                break;
            case '.':
                putchar(*pointer);
                break;
            case ',':
                *pointer = getchar();
                break;
            case '[':
                if (!*pointer) {
                    loop_counter = 1;
                    while (loop_counter) {
                        instruction = source[++i];
                        if (instruction == ']')
                            --loop_counter;
                        else if (instruction == '[')
                            ++loop_counter;
          }
        }
            break;
            case ']':
                if (*pointer) {
                    loop_counter = 1;
                    while (loop_counter > 0) {
                        instruction = source[--i];
                        if (instruction == '[') {
                            --loop_counter;
                        }
                        else if (instruction == ']') {
                            ++loop_counter;
                        }
                    }
                }
                break;
            default:
                printf("Incorrect character.");
                exit(EXIT_FAILURE);
        }

    }
    return 0;

}


int main(int argc, char *argv[]) {

    if (argc == 2) {

        file_name = argv[1];

        char *source = load_code();

        size_t memory_size = sizeof(source)/sizeof(source[0]);

        bf_interpreter(source, memory_size);

        printf("\n");

        free(source);

    }
    else {
        printf("Usage ./brainterpreter <filename.bf>\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
