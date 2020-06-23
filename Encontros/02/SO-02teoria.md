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
* Extraído de `man 3 opendir` no macOS
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
* Experimentos:
```shell
$ ./redireciona 
$ ./redireciona > saida.txt
$ ./redireciona 2> erro.txt
$ ./redirecona > saída.txt 2> erro.txt
```

## Metadados

* Chamadas de sistema
  * `stat` : coleta diversas informações
  * `lstat` : variação de `stat` que difere no tratamento de _link_ simbólico (não o segue; retorna seus metadados)
  * `fstat` : variação de `stat` que recebe descritor de arquivos
  * Estrutura de dados `stat`

Tudo no mesmo `man 2 stat`

## Estrutura de dados `stat`

``` 
$ man 2 stat
```
* Discussão seguinte aplica-se ao macOS Catalina
    * Há variações entre fabricantes
    * Confira especifidades do seu sistema

``` 
     struct stat { /* when _DARWIN_FEATURE_64_BIT_INODE is defined */
         dev_t           st_dev;           /* ID of device containing file */
         mode_t          st_mode;          /* Mode of file (see below) */
         nlink_t         st_nlink;         /* Number of hard links */
         ino_t           st_ino;           /* File serial number */
         uid_t           st_uid;           /* User ID of the file */
         gid_t           st_gid;           /* Group ID of the file */
         dev_t           st_rdev;          /* Device ID */
         struct timespec st_atimespec;     /* time of last access */
         struct timespec st_mtimespec;     /* time of last data modification */
         struct timespec st_ctimespec;     /* time of last status change */
         struct timespec st_birthtimespec; /* time of file creation(birth) */
         off_t           st_size;          /* file size, in bytes */
         blkcnt_t        st_blocks;        /* blocks allocated for file */
         blksize_t       st_blksize;       /* optimal blocksize for I/O */
         uint32_t        st_flags;         /* user defined flags for file */
         uint32_t        st_gen;           /* file generation number */
         int32_t         st_lspare;        /* RESERVED: DO NOT USE! */
         int64_t         st_qspare[2];     /* RESERVED: DO NOT USE! */
     };
```
Diversos metadados estão nos _inodes_.

### Sobre tipos específicos dos _header files_ das chamadas de sistema

* Em geral, podem ser redefinições de tipos numéricos sem sinal
    * Compatíveis com `long long unsigned`
    * `%llu` no `printf`

### Sobre mascaramento de _bits_ 

Quando a informação requer poucos bits, é comum agregar várias informações em uma palavra.

Cada _campo de bits_ da palavra representa uma informação. A palavra funciona como um "registro feito de bits".

Para ler um campo, é preciso "mascarar" os demais, realizando um "e bit a bit" (_bitwise and_) entre a palavra e
a máscara. A máscara é composta de 0s nas respectivas posições dos campos ignorados, e 1s no campo de interesse.

Exemplo:

* Código de 4 bits para registro de ventos.
    * Bit 3
        * 1 : Dia
        * 0 : Noite
    * Bits 2-0 (3 bits)
        * 111 : Norte
        * 110 : Nordeste
        * 101 : Leste
        * 100 : Sudeste
        * 011 : Sul
        * 010 : Sudoeste
        * 001 : Oeste
        * 000 : Noroeste

* A palavra `1001` registra noite ou dia?
```
 1001 - Dado
 1000 - Máscara
 ----
 1000 - Para análise do programa
```

    * Programação em C
    

## Empurrando

mkdir
rmdir  