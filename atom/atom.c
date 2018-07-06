/*
 * @Author: Terry Lei
 * @Email: terrylei@126.com
 * @Brief: Use hash table to manage strings.
 *  
 *  Examele:
 *   ---      ----      ----
 *  | 0 | -> |atom| -> |atom| -> NULL
 *   ---      ----      ----
 *  | 1 | -> NULL
 *   ---
 *  |...| -> NULL
 *   ---
 */
#include "atom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_TABLE_SIZE   (256)

struct atom {
    struct atom *next;
    int         len;
    char        str[0];
};

static struct atom * s_hash_table[MAX_TABLE_SIZE] = {0};

static unsigned long hash_string(const char *str)
{
    unsigned long hash = 0;
    int i;
    for (i = 0; i < strlen(str); i++) 
        hash = hash + (hash << 5) + str[i];
    return hash;
}

const char * atom_string(const char *str)
{
    int len = strlen(str);
    int hash = hash_string(str) % MAX_TABLE_SIZE;

    /* Check if already exists */
    struct atom *p;
    for (p = s_hash_table[hash]; p != NULL; p = p->next) {
        if (p->len == len) {
            int i;
            for (i = 0; i < len; i++) {
                if (p->str[i] != str[i])
                    break;
            }
            if (i == len)
                return p->str; 
        }
    }

    /* Create a new atom */
    struct atom *atom = malloc(sizeof(struct atom) + len + 1);
    atom->len = len;
    strcpy(atom->str, str);

    /* Insert to head */
    atom->next = s_hash_table[hash];
    s_hash_table[hash] = atom; 

    return atom->str;
}

const char * atom_int(long num)
{
    char str[32] = {0};
    char *s = str + sizeof(str) - 1;
    unsigned long m;

    if (num == LONG_MIN)
        m = LONG_MAX + 1UL;
    else if (num < 0)
        m = -num;
    else
        m = num;
   
    do {
        *--s = m % 10 + '0';
        m = m / 10;
    } while (m != 0);

    if (num < 0)
        *--s = '-';

    return atom_string(s);
}

