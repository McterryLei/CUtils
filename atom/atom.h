/*
 * @Author: Terry Lei
 * @Email: terrylei@126.com
 * @Brief: An atom is a point to a unique, immutable string.
 *         Atoms are often used as keys in data structures like Map.
 */
#ifndef C_ATOM_H
#define C_ATOM_H

/* Create a new atom with new copy the string */
const char * atom_string(const char *str);

/* Create a new atom of string represent of number */
const char * atom_int(long num);

#endif
