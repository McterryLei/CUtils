#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int linenum = 0;

void doubleword(FILE *fp, const char *filename);
bool getword(FILE *fp, char *buf, int size);
void print_doubleword(const char *filename, const char *word);

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror(argv[i]);
            return EXIT_FAILURE;
        }

        doubleword(fp, argv[i]);
        fclose(fp);
    } 

    if (argc == 1) 
        doubleword(stdin, NULL);

    return EXIT_SUCCESS;
}

void doubleword(FILE *fp, const char *filename)
{
    int double_count = 0;
    char prev[128], word[128];    
    prev[0] = '\0';

    while (getword(fp, word, sizeof(word))) {
        if (isalpha(word[0]) && strcmp(word, prev) == 0) {
            if (double_count <= 0) 
                print_doubleword(filename, word);

            double_count++;
        }
        else {
            double_count = 0;
        }

        strcpy(prev, word);
    } 
}

bool getword(FILE *fp, char *buf, int size)
{
    /* scan forward to a nonspace charactor */
    int c = getc(fp);
    for (; c != EOF && isspace(c); c = getc(fp))
        if (c == '\n')
            linenum++;

    /* copy word into buf[0..size-1] */
    int i = 0;
    for (; c != EOF && !isspace(c); c = getc(fp))
        if (i < size - 1)
            buf[i++] = tolower(c);
    if (i < size)
        buf[i] = '\0';     

    if (c != EOF)
       ungetc(c, fp); //put back 
    
    return buf[0] != '\0';
}

void print_doubleword(const char *filename, const char *word)
{
    if (filename != NULL)
        printf("%s:", filename); 
    printf("%d: %s\n", linenum, word);
}
