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