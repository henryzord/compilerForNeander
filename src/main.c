#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <stdbool.h>

#include <string.h>  // você vai precisar desta biblioteca para processar as strings

#define SIZE_TEMP_BUFF 500
#define SIZE_VAR_BUFF 50
#define START_MEM_POS 80

/**
 * Compila uma string escrita em C para Neander-X.
 *
 * @param file_contents Uma string com código-fonte em C.
 * @return Uma string com o código-fonte em Neander-X.
 */
char *compile(char *file_contents) {
    char *code = (char*)malloc(sizeof(char) * 500000);  // 500 mil caracteres
    char *runner = code;
    int last_pos = START_MEM_POS;

    char temp[SIZE_TEMP_BUFF];
    char temp_pos[SIZE_VAR_BUFF];

    char *line = NULL;
    char *remaining_lines = NULL;
    line = strtok_s(file_contents, "\n", &remaining_lines);
    while(line != NULL) {
        if(
            (strstr(line, "#include") != NULL) ||
            (strstr(line, "int main(") != NULL) ||
            (strstr(line, "int main (") != NULL) ||
            (strlen(line) == 0)
        ) {
            // does nothing
        } else if(strstr(line, "return 0") != NULL) {
            strcpy(runner, "HLT\n");
            break;
        } else {
            char *word = NULL;
            char *remaining_words = NULL;
            bool capturing_name = false;
            bool capturing_value = false;
            char buffer_name[SIZE_VAR_BUFF];
            char buffer_value[SIZE_VAR_BUFF];

            word = strtok_s(line, " ;", &remaining_words);
            while(word != NULL) {
                if(capturing_name) {
                    strcpy(&buffer_name[0], word);

                    snprintf(temp_pos, sizeof temp_pos, "%dH", last_pos);
                    last_pos += 1;

                    snprintf(temp, sizeof temp, "%s EQU %s\n", buffer_name, temp_pos, buffer_value);
                    strcpy(runner, temp);
                    runner += strlen(temp);
                    capturing_name = false;
                } else if(capturing_value) {
                    strcpy(&buffer_value[0], word);
                    snprintf(temp, sizeof temp, "LDI %s\nSTA %s\n", buffer_value, buffer_name);
                    strcpy(runner, temp);
                    runner += strlen(temp);
                    capturing_value = false;
                } else if(strcmp(word, "int") == 0) {
                    capturing_name = true;
                } else if(strcmp(word, "=") == 0) {
                    capturing_value = true;
                } else if(strcmp(word, "//") == 0) {
                    break;  // ignores rest of line
                }
                else {
                    // does nothing
                }


                word = strtok_s(NULL, " ;", &remaining_words);
            }
        }
        line = strtok_s(NULL, "\n", &remaining_lines);
    }
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