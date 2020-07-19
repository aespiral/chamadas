#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    unsigned int delay = atoi(argv[1]);
    if (fork() != 0)
        exit(1);
    sleep(delay);
    printf("\nLembrete!");
    exit(2);
}
