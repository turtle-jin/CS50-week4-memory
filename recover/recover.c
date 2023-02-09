#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// number of bytes in a block
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // check for command line args
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open memory card
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file. \n");
        return 1;
    }

    // create a new type to store a byte of data
    typedef uint8_t BYTE;

    // create buffer array to read into file
    BYTE buffer[BLOCK_SIZE];

    // create a counter to keep track of jpg numbers
    int jpgs_count = 0;

    // create array to strore file name
    char filename[8];

    // create img file pointer and set it to NULL
    FILE *img = NULL;

    // create a jpeg header flag
    //int header_found = 0;


    // loop until the end of card
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //if start of new JPEG (detect by looking at first 4 bytes)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)  // close the previous file
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", jpgs_count);  //print filename

            // open new file img to write into
            img = fopen(filename, "w");
            // if fopen fails, return with error
            if (img == NULL)
            {
                printf("Could not create a new file.\n");
                return 1;
            }
            // write into very first file
            fwrite(buffer, 1, BLOCK_SIZE, img);
            jpgs_count++;
        }

        // if previous file is open, keep writing to it until new header is detected
        else if (img != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    // close any open file pointer
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(raw_file);

    return 0;
}
