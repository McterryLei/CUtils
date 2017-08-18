#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int linenum = 0;

void doubleword(FILE *fp, const char *filename);
bool getword(FILE *fp, char *buf, int size);
void print_doubleword(const char *word, const char *filename);

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
    char prev[128], cur[128];    
    prev[0] = '\0';

    while (getword(fp, cur, sizeof(cur))) {
        if (isalpha(cur[0]) && strcmp(cur, prev) == 0) 
            print_doubleword(cur, filename);
        strcpy(prev, cur);
    } 
}

bool getword(FILE *fp, char *buf, int size)
{
    /* scan forward to a nonspace charactor */
    int c = getc(fp);
    for (; isspace(c); c = getc(fp))
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

void print_doubleword(const char *word, const char *filename)
{
    if (filename != NULL)
        printf("%s:", filename); 
    printf("%d: %s\n", linenum, word);
}
