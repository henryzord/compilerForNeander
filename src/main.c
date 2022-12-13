#include <stdio.h>
#include "definitions.h"

#define BUFFER_SIZE 500

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(
            stderr,
            "Uso deste programa (pela linha de comando):\n\tcompiler <arquivo_a_ser_processado>"
        );
        return 0;
    }

    FILE * file_pointer;
    char buffer[BUFFER_SIZE];

    file_pointer = fopen(argv[1] , "r");
    if (file_pointer == NULL) {
        fprintf(
            stderr,
            "Não foi possível abrir o arquivo!"
        );
    } else {
        while(fgets(buffer , BUFFER_SIZE , file_pointer) != NULL) {
            printf("%s", buffer);
        }
        fclose(file_pointer);
    }
    return 0;
}