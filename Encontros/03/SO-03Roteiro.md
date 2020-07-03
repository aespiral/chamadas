# Encontro 03

* [Vídeo](https://www.youtube.com/playlist?list=PLGw6FOJ2oNsFsiKSK9qAnYl_kycXYEHmk)
* Tópicos
    * Erros nas chamadas de sistema
        * Variável `errno` (`#include <sys/errno.h`)
        * `man 2 errno`
        * Explorar erros em manuais (`man`) de chamadas
        * Forçar erros em programas
            * Exemplo: [`errado.c`](file://./errado.c)
    * Chamadas de sistema `open` e `close`
        * "Abrir arquivo"
            * [Seção 2.6 "_Opening a file_"](https://ocaml.github.io/ocamlunix/files.html#sec25)
            * [`man 2 open`](https://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html) 
            * Ler e entender os 12 flags de operação de `open`
        * "Fechar descritor"
            * [Seção 2.8 "_Closing a descriptor_"](https://ocaml.github.io/ocamlunix/files.html#sec32)
    * Chamadas de sistema `read` e `write`
        * "Ler arquivo" e "Escrever em arquivo"
            * [Seção 2.7 "_Reading and writing_"](https://ocaml.github.io/ocamlunix/files.html )
    * Chamada de sistema `lseek`
        * "Posicionar"
            * [Seção 2.12  "_Positioning_"](https://ocaml.github.io/ocamlunix/files.html)
            * Entender os 3 modos