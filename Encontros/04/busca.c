#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/wait.h>

// cond -> i == 57

int busca_simples(int* array, int inicio, int fim) {
    int j;
    for (j = inicio; j<fim; j++) {
        if ( array[j] == 57 )
            return 1;
    }
    return 0;
}

int busca_dividida(int* array, int inicio, int fim) {

    if (fork() == 0) {
        exit( busca_simples(array, (inicio + fim)/2 + 1, fim) );
    } else {
        int achou_aqui = busca_simples(array, inicio, (inicio + fim)/2);
        int res = 0;
        wait(&res);
        if (WIFEXITED(res))
            return achou_aqui || WEXITSTATUS(res);
        exit(-1);
    }
}

int main() {
    int a1[7] = { 1, 10, 11, 15, 20, 40, 70 };
    if (busca_dividida(a1, 0, 7))
        printf("Achou a1\n");
    else
        printf("Nao achou a1\n");

    int a2[7] = { 1, 57, 11, 15, 20, 40, 70 };
    if (busca_dividida(a2, 0, 7))
        printf("Achou a2\n");
    else
        printf("Nao achou a2\n");

    int a3[7] = { 1, 10, 11, 15, 20, 57, 70 };
    if (busca_dividida(a3, 0, 7))
        printf("Achou a3\n");
    else
        printf("Nao achou a3\n");

}
