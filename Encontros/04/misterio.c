#include <stdio.h>
#include <unistd.h>

int main() {
    int misterio = fork();
    if (misterio == 0)
        printf("Hello ");
    else
        printf("World ");
}