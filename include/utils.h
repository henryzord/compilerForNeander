#ifndef COMPILERFORNEANDER_DEFINITIONS_H
#define COMPILERFORNEANDER_DEFINITIONS_H

int write_file(char *destination, char *file_contents);
char *read_file(char *address);
int count_lines(char *file_contents);
char *get_line(char *file_contents, int line);

#endif //COMPILERFORNEANDER_DEFINITIONS_H
