#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"


#define BUFFER_SIZE 100

int count_characters(char *address) {
    char buffer[BUFFER_SIZE];
    int count = 0;

    FILE * file_pointer = fopen(address , "r");
    if (file_pointer == NULL) {
        fprintf(
                stderr,
                "Não foi possível abrir o arquivo!"
        );
        return -1;
    }

    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL) {
        count += (int)strlen(buffer) + 1;  // +1 para o \0 do fim da string
    }
    fclose(file_pointer);
    return count;
}

char *read_file(char *address) {
    int size = count_characters(address);
    if(size == -1) {
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    char *file_contents = (char*)malloc(sizeof(char) * size);
    char *ptr = file_contents;
    FILE *file_pointer = fopen(address , "r");

    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL) {
        for(int i = 0; buffer[i] != '\0'; i++) {
            *ptr = buffer[i];
            ptr++;
        }
    }
    fclose(file_pointer);
    return file_contents;
}

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
