#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv, char** envp) {
    // check if the argument with the filename is provided
    if (argc != 3) {
        fprintf(stderr, "not enough args");
        exit(2);
    }

    FILE *file1, *file2;

    file1 = fopen(argv[1], "r");
    if (file1 == NULL) {
        fprintf(stderr, "Error opening file 1");
        exit(1);
    }

    file2 = fopen(argv[2], "w+");
    if (file2 == NULL) {
        fprintf(stderr, "Error opening/creating file 2");
        exit(1);
    }

    char ch = (char)fgetc(file1);
    while (ch != EOF) {
        if (fputc(ch, file2) != ch) {
            fprintf(stderr, "Error writing to file");
            exit(1);
        }

        ch = (char)fgetc(file1);
    }

    fclose(file1);
    fclose(file2);

    return 0;
}