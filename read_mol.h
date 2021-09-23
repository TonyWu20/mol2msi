#include <stdio.h>
#define MAXLINE 80
typedef struct
{
    float x, y, z;
    char elm[2];
    int ItemId;
    char text[120];
} ATOM_BLOCK;
typedef struct
{
    int atom1, atom2, bondtype;
    int ItemId;
    char *bondtype_line;
    char text[120];
} BOND_BLOCK;

//CHAR_ARRAY returnLines(FILE *filepointer);
long int countLines(FILE *file);
int returnLines(char *lineptr[], FILE *filepointer);
ATOM_BLOCK build_atom(char s[], int id);
BOND_BLOCK build_bond(char s[], int id);
void output_msi(char *fileName, char *toWrite[], int lines);
int collect_atoms(int atomNum, char *s[], char *res[]);
int collect_bonds(int bondNum, char *s[], char *res[]);
