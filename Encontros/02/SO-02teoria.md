# Diretórios e metadados de arquivos

## Créditos
Principal referência: "Unix System Programming in OCaml",
Xavier Leroy e Didier Rémy, 2014

Licenciado sob a Creative Commons

## Estratégia de aprendizagem

Tentar associar:
*   Comando da _linha de comando_ 
```
rm delete.me
```      
* Chamada de sistema
```C 
main () {
  char* n = "delete.me";
  unlink(n);
}
```

## Objetivo

Escrever um programa em C que use as chamadas de sistema 
para realizar o mesmo que o seguinte comando faz:

```
$ ls -l
```
Análise:
* `ls` remete a acessar o arquivo-diretório
* `-l` remete a obter todos os metadados de cada entrada do diretório
  * tipo do arquivo (normal, diretório ou _link_ simbólico)
  * permissões de acesso
  * proprietários (usuário e grupos)
  * tempos de acesso
  * tamanho

Método:
* Fazendo requisições ao _kernel_ (chamadas de sistema se possível)

## Opendir (e readdir, closedir, rewinddir)
```
$ man 3 opendir
```
Resultado:
```
DIRECTORY(3)             BSD Library Functions Manual             DIRECTORY(3)

NAME
     opendir, fdopendir, readdir, readdir_r, telldir, seekdir, rewinddir,
     closedir, dirfd -- directory operations

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <dirent.h>

     DIR *
     opendir(const char *filename);
```

---
* Função em C (manual 3)
* Estrutura de dados `DIR`
* Funções associadas
   * `readdir`
   * `rewinddir`
   * `closedir`

Obs.: Kotlin Native, disponível na biblioteca `platform.posix`

---
```
           dirp = opendir(".");
           if (dirp == NULL)
                   return (ERROR);
           len = strlen(name);
           while ((dp = readdir(dirp)) != NULL) {
                   if (dp->d_namlen == len && strcmp(dp->d_name, name) == 0) {
                           (void)closedir(dirp);
                           return (FOUND);
                   }
           }
           (void)closedir(dirp);
           return (NOT_FOUND);
```   
* Extraído de 'man 3 opendir' no macOS
* É um programa exemplo 
   * Funcionalidade: dado um nome de arquivo, busca no diretório
* `readdir` é um iterador
   * A cada execução ele retorna uma entrada diferente
   * Retorna `NULL` quando termina
   
`readdir` (iterador) mantém internamente o estado do percurso

## Descritores de arquivos

* Duas formas de acessar arquivos
   * Nome
   * Descritor de arquivo
   
* Informações em tempo de execução vinculadas a um descritor de arquivo
   * Posição atual de escrita/leitura
   * Direitos de acesso
   * Acesso bloqueante ou não bloqueante
   * Sobrescrita ou _append_
   
* Descritores de arquivo padrão
   * `stdin` : número 0, _default_ é o teclado   
   * `stdout`: número 1, _default_ é a tela
   * `stderr`: número 2, _default_ é a tela

## Redirecionamentos
* `redireciona.c`
```c 
#include <stdio.h>
int main() {
  fprintf(stdout, "Saída!\n");
  fprintf(stderr, "ERRO!\n");
}
```
* Execuções
``` 
$ ./redireciona 
$ ./redireciona > saida.txt
$ ./redireciona 2> erro.txt
$ ./redirecona > saída.txt 2> erro.txt
```

## Empurrando

mkdir
rmdir  