#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* getopt */
#include <errno.h>

//  TODO(W3ndige): Compress the code from characters other than bf
//  TODO(W3ndige): Dynamic memory allocation - check all cases

extern int errno;

enum {
    READ_FILE, READ_ARG, READ_ERROR
};

char *load_code(FILE *input_file) {
    char *buffer = 0;

    fseek(input_file, 0, SEEK_END);
    size_t length = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    buffer = malloc(length);

    if (buffer) {
        fread(buffer, 1, length, input_file);
    }

    else if (!buffer) {
        perror("Malloc fail");
        exit(EXIT_FAILURE);
    }

    // Check for correct number of loops
    int balance = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        switch (buffer[i]) {
        case '[':
            balance++;
            break;
        case ']':
            balance--;
            break;
        }
    }
    if (balance < 0) {
        puts("End of the loop was encountered before the start");
        exit(EXIT_FAILURE);
    }
    else if (balance != 0) {
        puts("Unbalanced number of loops");
        exit(EXIT_FAILURE);
    }

    return buffer;
}

int run_bf(char *source_code, size_t memory_size) {
    // Allocate memory
    char *memory = calloc(memory_size, sizeof(int));
    char *pointer = memory;

    // Interpret instructions
    for (int i = 0; i < memory_size + 1; i++) {
        char instruction = source_code[i];
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
                size_t loop_counter = 1;
                while (loop_counter) {
                    instruction = source_code[++i];
                    if (instruction == ']')
                        --loop_counter;
                    else if (instruction == '[')
                        ++loop_counter;
                }
            }
            break;
        case ']':
            if (*pointer) {
                size_t loop_counter = 1;
                while (loop_counter > 0) {
                    instruction = source_code[--i];
                    if (instruction == '[') {
                        --loop_counter;
                    }
                    else if (instruction == ']') {
                        ++loop_counter;
                    }
                }
            }
            break;
        }
    }
    printf("\n");
    return 0;

}

int main(int argc, char *argv[]) {

    // How to read the file, input argument
    int input_mode;
    char *input_arg = "";

    // Parameter parsing
    int opt;
    while ((opt = getopt(argc, argv, "f:c:")) != -1) {
        switch (opt) {
        case 'f':
            input_mode = READ_FILE;
            input_arg = optarg;
            break;
        case 'c':
            input_mode = READ_ARG;
            input_arg = optarg;
            break;
        }
    }

    FILE * input_file;

    switch(input_mode) {
    case READ_FILE:
        input_file = fopen(input_arg, "r");
        if (!input_file) {
            perror("Error while opening file");
            exit(EXIT_FAILURE);
        }
        break;
    case READ_ARG:
        input_file = fmemopen(input_arg, strlen(input_arg), "r");
        break;
    }

    // Load the code from the file
    char *source_code = load_code(input_file);
    fclose(input_file);

    // Run the code
    size_t memory_size = strlen(source_code);
    run_bf(source_code, memory_size);

    free(source_code);

    return 0;
}
