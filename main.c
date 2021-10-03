#include "read_mol.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int itemId = 0;
int scanLineID = 3;

int main(int argc, char *argv[])
{
    printf("Parsing begins\n");
    int atomNum, bondNum;
    atomNum = bondNum = 0;
    long int lineNum = 0;
    char *buffer;
    /* read file */
    char *fileName = argv[1];

    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }
    if ((lineNum = countLines(file)) < 4)
    {
        printf("error: Not enough lines.\n");
    }
    else
    {
        char *strArray[lineNum];
        returnLines(strArray, file);
        /* Scan the 3rd line of .mol, to get numbers of atoms and bonds, and
         * increase scanLineID by 1 */
        sscanf(strArray[scanLineID++], "%d %d", &atomNum, &bondNum);
        printf("Number of atoms:%d, Number of bonds:%d\n", atomNum, bondNum);
        int resItemNum = atomNum + bondNum + 2;
        char *resArray[resItemNum];
        asprintf(&buffer,
                 "# MSI CERIUS2 DataModel File Version 4.0\n(%d Model\n",
                 itemId + 1);
        resArray[itemId++] = strdup(buffer);
        /* Get atoms x, y, z and element, format into .msi */
        /* scanLineID begins from 4 */
        collect_atoms(atomNum, strArray, resArray);
        collect_bonds(bondNum, strArray, resArray);
        resArray[itemId] = strdup(")\0");
        output_msi(fileName, resArray, itemId);
        printf("done!");
        return 0;
    }
}
