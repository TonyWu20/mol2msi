#include "read_mol.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ATOM_BLOCK build_atom(char line[], int id)
{
    ATOM_BLOCK atom;
    char *buffer;
    atom.ItemId = id;
    sscanf(line, "%f %f %f %s", &atom.x, &atom.y, &atom.z, atom.elm);
    asprintf(&buffer,
             "  (%d Atom\n    (A C ACL \"%d %s\")\n    (A C Label "
             "\"%s\")\n    (A D XYZ (%f %f %f))\n    (A I Id %d)\n  )\n",
             atom.ItemId, atom.ItemId, atom.elm, atom.elm, atom.x, atom.y,
             atom.z, atom.ItemId);
    strcpy(atom.text, buffer);
    return atom;
}

BOND_BLOCK build_bond(char line[], int id)
{
    BOND_BLOCK bond;
    char *buffer;
    sscanf(line, "%d %d %d", &bond.atom1, &bond.atom2, &bond.bondtype);
    if (bond.bondtype > 1)
    {
        asprintf(&bond.bondtype_line, "    (A I Type %d)\n", bond.bondtype);
    }
    else
    {
        bond.bondtype_line = "";
    }
    asprintf(&buffer,
             "  (%d Bond\n    (A O Atom1 %d)\n    (A O Atom2 %d)\n%s  )\n", id,
             bond.atom1 + 1, bond.atom2 + 1, bond.bondtype_line);
    strcpy(bond.text, buffer);
    return bond;
}

int collect_atoms(int atomNum, char *s[], char *res[])
{
    int i, j;
    extern int scanLineID;
    extern int itemId;
    for (i = 0, j = itemId; i < atomNum; i++)
    {
        ATOM_BLOCK atom;
        atom = build_atom(s[scanLineID++], ++itemId);
        res[j++] = strdup(atom.text);
    }
    if (i > 0)
        return i;
    else
    {
        printf("Error: No atoms collected!");
        return 0;
    }
}
int collect_bonds(int bondNum, char *s[], char *res[])
{
    int i, j;
    extern int scanLineID;
    extern int itemId;
    for (i = 0, j = itemId; i < bondNum; i++)
    {
        BOND_BLOCK bond;
        bond = build_bond(s[scanLineID++], ++itemId);
        res[j++] = strdup(bond.text);
    }
    if (i > 0)
        return i;
    else
    {
        printf("Error: No bonds collected!");
        return 0;
    }
}
