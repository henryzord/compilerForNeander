#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(
            stderr,
            "Uso deste programa (pela linha de comando):\n\tcompiler <arquivo_a_ser_processado>"
        );
        return 0;
    }
    char *file_contents = read_file(argv[1]);
    if(file_contents == NULL) {
        return 1;
    }
    char *ptr = file_contents;

    int hit = 0;
    while(*ptr != '\0') {
        int length = 0;
        char *previous = ptr;
        while((*ptr != '\n') && (*ptr != '\0')) {
            length += 1;
            ptr++;
        }
        printf("comprimento = %02d: ", length);
        while((*previous != '\n' && (*previous != '\0'))) {
            printf("%c", *previous);
            previous++;
        }
        printf("\n");
        ptr++;
        hit++;
    }
    free(file_contents);

    return 0;
}