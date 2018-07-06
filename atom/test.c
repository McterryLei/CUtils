#include "atom.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv)
{
    const char *key1 = atom_string("username");
    const char *key2 = atom_string("username");
    assert(key1 == key2);

    assert(atom_int(1) == atom_string("1"));
    assert(atom_int(2) == atom_int(2));

    return 0;
}
