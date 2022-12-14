#ifndef UTILS_H
#define UTILS_H

/**
 * Escreve uma string em um arquivo.
 *
 * @param destination O caminho do arquivo a ser escrito, por exemplo C:\\Users\\aluno\\neander.asm
 * @param file_contents A string a ser escrita
 * @return 0 se tudo correr normalmente, -1 se ocorrer um erro
 */
int write_file(char *destination, char *file_contents);
/**
 * Dada uma string para um arquivo (e.g. C:\\Users\\aluno\\input.c), retorna uma string com o conteúdo do arquivo
 *
 * @param address Caminho para um arquivo no computador, por exemplo C:\\Users\\aluno\\input.c
 * @return O conteúdo do arquivo como uma string dinamicamente alocada
 */
char *read_file(char *address);
/**
 * Conta quantas linhas uma string possui. Em outras palavras, conta o número de caracteres '\n' e adiciona 1
 *
 * @param file_contents Uma string
 * @return O número de linhas da string + 1
 */
int count_lines(char *file_contents);
/**
 * Retorna uma determinada linha em uma string. Começa a contar a partir do zero
 *
 * @param file_contents Uma string
 * @param line A linha a ser retornada, dentro desta string. A contagem começa a partir de zero
 * @return A linha solicitada
 */
char *get_line(char *file_contents, int line);

#endif // UTILS_H
