#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#include <string.h>  // você vai precisar desta biblioteca para processar as strings

/**
 * Compila uma string escrita em C para Neander-X.
 *
 * @param file_contents Uma string com código-fonte em C.
 * @return Uma string com o código-fonte em Neander-X.
 */
char *compile(char *file_contents) {
    // TODO desenvolva seu código aqui
    char *code = (char*)malloc(sizeof(char) * 82);
    code = strcpy(code,
        "A EQU 80H\n"
        "B EQU 81H\n"
        "C EQU 82H\n"
        "LDI 1\n"
        "STA A\n"
        "LDI 2\n"
        "STA B\n"
        "LDA A\n"
        "ADD B\n"
        "STA C\n"
        "OUT 0\n"
        "HLT\n"
    );  // essa string possui 82 caracteres, por isso alocamos 82 caracteres com malloc
    // TODO desenvolva seu código aqui
    return code;
}

int main(int argc, char **argv) {
    if(argc != 3) {
        fprintf(
            stderr,
            "Uso deste programa (pela linha de comando):\n\tcompiler <arquivo_c> <arquivo_neander>"
        );
        return 0;
    }
    char *c_code = read_file(argv[1]);
    if(c_code == NULL) {
        return 1;
    }
    int c_n_lines = count_lines(c_code);
    printf("o codigo C possui %d linhas\n", c_n_lines);
    printf("----------------------------\n");
    printf("O conteudo do codigo C e':\n");
    printf("----------------------------\n");
    for(int i = 0; i < c_n_lines; i++) {
        char *line = get_line(c_code, i);
        printf("%s\n", line);
        free(line);
    }
    char *neander_code = compile(c_code);
    int neander_n_lines = count_lines(neander_code);
    printf("O codigo neander possui %d linhas\n", neander_n_lines);
    printf("----------------------------\n");
    printf("O conteudo do codigo Neander-X e':\n");
    printf("----------------------------\n");
    for(int i = 0; i < neander_n_lines; i++) {
        char *line = get_line(neander_code, i);
        printf("%s\n", line);
        free(line);
    }
    write_file(argv[2], neander_code);
    free(c_code);
    free(neander_code);
    return 0;
}