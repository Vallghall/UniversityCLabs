#include <unistd.h>
#include <errno.h>
#include "stdlib.h"
#include "stdio.h"
#include "dirent.h"

void fatalf(char* msg, int code);
void read_wd(char* dir_name);

int main(int argc, char** argv, char** envp) {
    // catalogue name should be passed
    if (argc != 2)
        fatalf("wrong number of arguments", 1);

    // printing content of the current directory
    char *cwd = getcwd(NULL, 0);
    if (cwd == NULL)
        fatalf("failed to get current directory name", 2);

    puts("Files in the current working directory:");
    read_wd(cwd);

    // printing content of the directory from args
    puts("Files in the given directory:");
    read_wd(argv[1]);


    return 0;
}

void fatalf(char* msg, int code) {
    fprintf(stderr, "%s", msg);
    exit(code);
}

void read_wd(char* dir_name) {
    DIR* dir = opendir(dir_name);
    if (dir == NULL) {
        fprintf(stderr, "failed to open directory \"%s\"", dir_name);
        exit(1);
    }

    struct dirent *d;
    while (1) {
        d = readdir(dir);
        if (d == NULL) {
            if (errno == EIO) {
                perror("failed to rea dir entry");
                exit(errno);
            }

            break;
        }

        printf("\t%s\n", d->d_name);
    }

    free(d);
    closedir(dir);
}
