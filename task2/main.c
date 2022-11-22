#include "stdio.h"
#include "stdlib.h"
#include "signal.h"


static volatile sig_atomic_t keep_running = 1;
// sig_handle - handles keyboard interrupt
void sig_handler(int _) {
    keep_running = 0;
}

int main(int argc, char** argv, char** envp) {
    // check if the argument with the filename is provided
    if (argc != 2) {
        fprintf(stderr, "agr is not provided");
        exit(2);
    }

    FILE* f = fopen(argv[1], "w+");

    puts("Write symbols one by one.\nTo exit, enter Crtl+C...\n");
    signal(SIGINT, sig_handler); // keyboard interrupt handler set
    while (keep_running) {
        char input_sym = 0;
        scanf("%c", &input_sym);
        if (input_sym < '\n')
            continue;

        if (fputc(input_sym, f) != input_sym) {
            perror("file write error");
            exit(2);
        }
    }

    fclose(f);
    puts("Closed by Ctrl+C...");

    return 0;
}