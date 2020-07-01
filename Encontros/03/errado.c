#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("delete.me", O_RDONLY, 0);
    printf("%d\n", errno);
    perror("O erro foi: ");
    return 0;
}