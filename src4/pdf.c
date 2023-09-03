#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

// section 4:
// Testing if a file is a PDF file

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./pdf filename\n");
        return 1;
    }

    // Open a file
    FILE *input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[4];

    // Reading a file
    fread(buffer, 1, 4, input);

    for (int i = 0; i < 4; i++)
    {
        // PDF file format contains first four bytes as 37 80 68 70
        printf("%i ", buffer[i]);
    }

    // Checking if a file is PDF File
    if(buffer[0] == 37 && buffer[1] == 80 && buffer[2] == 68 && buffer[3] == 70)
    {
        printf("\nInput File is a PDF File.\n");
    }
    else
    {
        printf("\nInput File is not a PDF File.\n");
    }

    fclose(input);
}