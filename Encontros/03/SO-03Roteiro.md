# Encontro 03

* Tópicos
    * Erros nas chamadas de sistema
        * Variável `errno` (`#include <sys/errno.h`)
        * `man 2 errno`
        * Explorar erros em manuais (`man`) de chamadas
        * Forçar erros em programas
    * Chamadas de sistema `open` e `close`
        * "Abrir arquivo"
        * https://ocaml.github.io/ocamlunix/files.html ,
            * Seção 2.6 "_Opening a file_"
            * Seção 2.8 "_Closing a descriptor_"
        * https://pubs.opengroup.org/onlinepubs/9699919799/functions/open.html (manual _online_)
        * Ler e entender os 12 flags de operação de `open`
    * Chamadas de sistema `read` e `write`
        * "Ler arquivo" e "Escrever em arquivo"
        * https://ocaml.github.io/ocamlunix/files.html , Seção 2.7 "_Reading and writing_"
    * Chamada de sistema `lseek`
        * "Posicionar"
        * https://ocaml.github.io/ocamlunix/files.html , Seção 2.12  "_Positioning_"