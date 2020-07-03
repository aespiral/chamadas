#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("delete.me", O_RDONLY, 0);
    printf("\nENOENT corresponde ao erro de no %d e o número obtido foi %d\n", ENOENT, errno);
    if (errno == ENOENT)
        printf("\nErro ENOENT (significaria 'NO ENTry' - 'nenhuma entrada'?) \n");
    perror("\nMensagem de erro em uma apresentação amigável, dada pelo sistema: ");

    return 0;
}