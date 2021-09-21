#include "read_mol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CHAR_ARRAY returnLines(FILE *file)
{
    CHAR_ARRAY returned;
    char *line = NULL; /* line array */
    size_t len = 0;
    ssize_t read;
    int counter = 0;
    /* char content[MAX_NUM_LINES][MAX_LINE_LENGTH]; */

    while ((read = getline(&line, &len, file)) !=
           -1) /* loop thru lines and add them to strArray */
    {
        /* fgets(line, 100, file) */
        int i = 0;
        while (line[i] != '\n')
        {
            returned.v[counter][i] = line[i];
            i++;
        }
        counter++;
    }
    return returned;
}

void output_msi(char *fileName, CHAR_ARRAY toWrite, int lines)
{
    int i;
    /*char *fileStem;*/
    FILE *fp;

    char *temp = malloc(strlen(fileName) + 1);
    strcpy(temp, fileName);
    strtok(temp, ".");
    strcat(temp, ".msi");
    free(temp);
    fp = fopen(temp, "w");
    for (i = 0; i <= lines; ++i)
    {
        fputs(toWrite.v[i], fp);
    }
    fclose(fp);
}
