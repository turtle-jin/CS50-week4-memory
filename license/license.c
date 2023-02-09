#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7]; 

    // Create array to store plate numbers
    char *plates[8]; // array of 8 pointers

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile))
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';


        // allocate space for each char
        plates[idx] = malloc(7 * sizeof(char));

        // copy buffer into plate array
        strcpy(plates[idx], buffer);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < 8; i++)
    {
        free(plates[i]);
    }


    fclose(infile);

    return 0;
}
