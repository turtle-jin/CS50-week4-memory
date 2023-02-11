#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

const int HEADER_SIZE = 44;  // Number of bytes in wav header

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    // Read header from the input file into an array
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, input_file);

    // Use check_format to ensure WAV format
    if (check_format(header) != 0)
    {
        printf("Not a WAV file!\n");
        return 1;
    }


    // Open output file for writing
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        printf("Could not open output file.\n");
        return 1;
    }

    // Write header to file
    fwrite(&header, HEADER_SIZE, 1, output_file);

    // Use get_block_size to calculate size of block
    long block_size = get_block_size(header);
    //printf("block size is %li.\n", block_size);


    // Declare an array to store each block
    BYTE buffer[block_size];

    //current position of file pointer
    //long current_position = ftell(input_file);


    // move the file pointer to the end of file
    fseek(input_file, 0, SEEK_END);

    // position of file pointer at the end of file
    long end_position = ftell(input_file);
    printf("The pointer position at the end of file is %ld\n", end_position);


    // calculate the total bytes of audio data (end_position - 44) and set up loop
    for (long i = block_size; i <= end_position - HEADER_SIZE; i += block_size)
    {
        fseek(input_file, -i, SEEK_END);  //start at the end of the file, going backwards 4 bytes each time
        fread(buffer, block_size, 1, input_file);
        fwrite(buffer, block_size, 1, output_file);

    }

    // close all the openned files
    fclose(input_file);
    fclose(output_file);
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int get_block_size(WAVHEADER header)
{
    // calculate block size by multiplying numer of channels and bytes per sample
    int block_size = header.numChannels * (header.bitsPerSample / 8);
    return block_size;
}