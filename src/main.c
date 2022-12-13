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
    int n_lines = count_lines(file_contents);
    printf("o documento possui %d linhas\n", n_lines);
    printf("----------------------------\n");
    printf("O conteúdo do documento é:\n");
    printf("----------------------------\n");
    for(int i = 0; i < n_lines; i++) {
        char *line = get_line(file_contents, i);
        printf("%s\n", line);
        free(line);
    }
    free(file_contents);
    return 0;
}