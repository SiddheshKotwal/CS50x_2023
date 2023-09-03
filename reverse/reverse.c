#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // ensure the program accepts two command-line arguments input WAV file and the output WAV file
    if (argc != 3)
    {
        printf("./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    // Checking for file if NULL
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Declaring wavheader datatype to store header of wav file
    WAVHEADER header;

    // Read header of wav file
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    if (check_format(header) == 0)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file

    // Array to read input file and write output file simultaneously
    uint8_t buffer[block_size];  // data type uint8_t refers to unsigned int of 8bits / 1byte
    // seeking 4 bytes after end
    fseek(input, block_size, SEEK_END);

    // while condition till 44 bytes as it contains header
    while (ftell(input) - block_size > sizeof(header))
    {
        fseek(input, -2 * block_size, SEEK_CUR);
        fread(&buffer, block_size, 1, input);
        fwrite(&buffer, block_size, 1, output);
    }

    // closing of all files
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // Checking if the input file is WAV file as its header contains 'WAVE' marker in file format
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        // Input File is WAV file
        return 1;
    }
    else
    {
        // Input File is not a WAV file
        return 0;
    }
}

int get_block_size(WAVHEADER header)
{
    int blocksize;
    // Calculating Blocksize of wav file
    blocksize = header.numChannels * (header.bitsPerSample / 8);
    return blocksize;
}