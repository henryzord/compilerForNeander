#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


#define BUFFER_SIZE 100

/**
 * Dada uma string para um arquivo (e.g. C:\Users\aluno\input.c), calcula quantos caracteres o arquivo tem
 *
 * @param address Caminho para um arquivo no computador, por exemplo C:\Users\aluno\input.c
 * @return O número de caracteres do arquivo, +1 para o caractere terminador
 */
int count_characters(char *address) {
    char buffer[BUFFER_SIZE];
    int count = 0;

    FILE * file_pointer = fopen(address , "r");
    if (file_pointer == NULL) {
        fprintf(
                stderr,
                "Nao foi possivel abrir o arquivo para leitura!"
        );
        return -1;
    }
    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL) {
        char *ptr = &buffer[0];
        while((*ptr != '\0') && (*ptr != '\n')) {
            count += 1;
            ptr++;
        }
        count += 1;
        // count += (int)strlen(buffer) + 1;  // +1 para o \0 do fim da string
    }
    fclose(file_pointer);
    return count;
}

/**
 * Escreve uma string em um arquivo.
 *
 * @param destination O caminho do arquivo a ser escrito, por exemplo C:\Users\aluno\neander.asm
 * @param file_contents A string a ser escrita
 * @return 0 se tudo correr normalmente, -1 se ocorrer um erro
 */
int write_file(char *destination, char *file_contents) {
    FILE *fptr = fopen(destination,"w");

    if(fptr == NULL) {
        fprintf(
                stderr,
                "Nao foi possivel abrir o arquivo para escrita!"
        );
        return -1;
    }
    int n_lines = count_lines(file_contents);
    for(int i = 0; i < n_lines; i++) {
        char *line = get_line(file_contents, i);
        fprintf(fptr,"%s\n", line);
        free(line);
    }
    fclose(fptr);
    return 0;
}

/**
 * Dada uma string para um arquivo (e.g. C:\Users\aluno\input.c), retorna uma string com o conteúdo do arquivo
 *
 * @param address Caminho para um arquivo no computador, por exemplo C:\Users\aluno\input.c
 * @return O conteúdo do arquivo como uma string dinamicamente alocada
 */
char *read_file(char *address) {
    int size = count_characters(address);
    if(size == -1) {
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    char *file_contents = (char*)malloc(sizeof(char) * size);
    char *copy = file_contents;
    FILE *file_pointer = fopen(address , "r");

    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL) {
        char *ptr = &buffer[0];
        while(*ptr != '\0') {
            *copy = *ptr;
            ptr++;
            copy++;
        }
    }
    *copy = '\0';
    fclose(file_pointer);
    return file_contents;
}

/**
 * Conta quantas linhas uma string possui. Em outras palavras, conta o número de caracteres '\n' e adiciona 1
 *
 * @param file_contents Uma string
 * @return O número de linhas da string + 1
 */
int count_lines(char *file_contents) {
    char *ptr = file_contents;
    int n_lines = 0;
    while(*ptr != '\0') {
        if(*ptr == '\n') {
            n_lines += 1;
        }
        ptr++;
    }
    return n_lines + 1;
}

/**
 * Retorna uma determinada linha em uma string. Começa a contar a partir do zero
 *
 * @param file_contents Uma string
 * @param line A linha a ser retornada, dentro desta string. A contagem começa a partir de zero
 * @return A linha solicitada
 */
char *get_line(char *file_contents, int line) {
    int n_lines = count_lines(file_contents);
    if(line < 0 || line >= n_lines) {
        fprintf(stderr, "A linha solicitada deve estar entre 0 <= line < n_lines!");
        return NULL;
    }
    char *ptr = file_contents;
    int cur_line = 0;
    while(*ptr != '\0') {
        if(cur_line == line) {
            break;
        }
        if(*ptr == '\n') {
            cur_line += 1;
        }
        ptr++;
    }
    int line_size = 0;
    char *previous_ptr = ptr;
    while((*ptr != '\n') && (*ptr != '\0')) {
        line_size += 1;
        ptr++;
    }
    ptr = previous_ptr;
    char *buffer = (char*)malloc(sizeof(char) * (line_size + 1));
    char *previous_buffer = buffer;
    while((*ptr != '\n') && (*ptr != '\0')) {
        *buffer = *ptr;
        buffer++;
        ptr++;
    }
    *buffer = '\0';
    return previous_buffer;
}
