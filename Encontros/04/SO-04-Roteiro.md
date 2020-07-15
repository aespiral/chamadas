# Processos

![](imagens/intro.svg)

Vídeo: https://youtu.be/rn2c7oA293s

## Mistério
Observe o seguinte programa:

```c 
#include <stdio.h>
#include <unistd.h>

int main() {
    int misterio = fork();
    if (misterio == 0)
        printf("Hello ");
    else
        printf("World ");
}
```

* Qual será o resultado da execução do programa?
    * O que é `fork`? O que retorna?
    * Qual `printf` será executado? "Hello " ou "World "?
    
* Resposta
    * `World Hello `
    * Os dois !!! 💣😲

![](imagens/fork.svg)

https://ocaml.github.io/ocamlunix/processes.html#sec67

## Linha de comando

Como o usuário (não o programador), visualiza processos

* Um processo infinito
    * `$ yes`
        * Ops! CONTROL + C
* _Jobs_ na linha de comando
    * Em desuso
    * `$ jobs`
    * `$ yes > /dev/null`
    * CONTROL + Z
        * Suspensão
    * `$ jobs`
    * `$ bg` : _background_
        * Continuação, retomada
    * `$ jobs`
    * `$ fg` : _foreground_
        * CONTROL + C 
* `&`
    * `$ yes > /dev/null &`
    * Lança, suspende e continua
* `$ ps`
    * `$ ps aux` : todos os processos do sistema, com todos os dados
        * `man ps`
    * `$ top`

## `leave`

* Comando `leave`
    * `$ leave 0945`
    * Programa exemplo
        * https://ocaml.github.io/ocamlunix/processes.html#sec68
    * Versão simplificada
```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    unsigned int delay = atoi(argv[1]);
    if (fork() != 0)
        exit(0);
    sleep(delay);
    printf("\nLembrete!");
    exit(0);
}
```

## Resumo

* Chamadas de sistema
    * `fork`
    * `getpid`
* Funções
    * `sleep`
* Comandos
    * `jobs`
    * `ps`
    * `top`
    * CONTROL + Z, `bg`, `fg`, `&` 
    * CONTROL + C