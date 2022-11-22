#include "stdio.h"
#include "stdlib.h"
#include "mem.h"
#include <conio.h>

int file_size(FILE*);
char* readAll(FILE*);
char* readByNLines(FILE*,int);

int main(int argc, char** argv, char** envp) {
    // check if the argument with the filename is provided
    if (argc != 3) {
        fprintf(stderr, "not enough args");
        exit(2);
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("could not open file");
        exit(errno);
    }

    int N = strtol(argv[2], (char**)NULL, 10);

    if (N == 0) {
        puts(readAll(f));
        fclose(f);
        return 0;
    }

    readByNLines(f, N);
    fclose(f);
    return 0;
}

int file_size(FILE* f) {
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    return size;
}

char* readAll(FILE* file) {
    char sym = (char)getc(file);
    char* f_content = (char*) calloc(file_size(file),sizeof(char));
    int count = 0;
    while (sym != EOF) {
        sym = (char)getc(file);
        f_content[count++] = sym;
    }

    return f_content;
}

char* readByNLines(FILE* file, int line_limit) {
    int max_part_buf = 128 * line_limit;
    char* part_buf = (char*) calloc(max_part_buf, sizeof(char));

    char sym;
    int ch_count = 0, line_count = 0;
    while (1) {
        sym = (char)getc(file);
        if (sym == 0) {
            fprintf(stderr, "Error reading char from file");
            exit(1);
        }
        if (sym == EOF) break;

        if (ch_count == max_part_buf) {
            max_part_buf += 128;
            part_buf = realloc(part_buf, max_part_buf);
            if (part_buf == NULL) {
                fprintf(stderr,"Error reallocating memory");
                exit(1);
            }
        }

        part_buf[ch_count++] = sym;
        if (sym == '\n') {
            line_count++;
            if (line_count != line_limit)
                continue;

            line_count = 0, ch_count = 0;
            printf("%sPress ENTER key to continue...", part_buf);
            getch();
            printf("\b\r                                      \r");

            max_part_buf = 128 * line_limit;
            part_buf = realloc(part_buf, max_part_buf);
            memset(part_buf, 0, max_part_buf);
        }
    }

    puts(part_buf);
    return 0;
}
