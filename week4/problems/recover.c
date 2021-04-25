#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

#define block 512

void create_file(void);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./recover image\n");
        return 1;
    }

    FILE *input = fopen("card.raw", "r");
    if (!input)
    {
        printf("Could not open file.\n");
    }

    char filename[20];
    int count = 0;
    bool new = true;
    bool found = false;

    // Pointer to be resued after creating file
    FILE *fpt = NULL;

    uint8_t bytes[block];

    // Read until end of the file
    while (fread(bytes, sizeof(uint8_t), block, input) != 0)
    {

        // If the first four bytes meet the critiera
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff
            && ((bytes[3] & 0xf0) == 0xe0))
        {

            // Check if this is the first file to be created
            if (!new)
            {
                // If not close the file
                fclose(fpt);
            }

            // Store new file name
            sprintf(filename, "%03i.jpg", count);

            FILE *output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Cannot open file.\n");
                return 1;
            }

            // File pointer to keep writing unti a new file
            fpt = output;
            fwrite(bytes, sizeof(uint8_t), block, fpt);

            // Update file name if a new file is created
            count++;
            new = false;
            found = true;
        }
        else
        {
            // If a new file is created, keep adding to that file
            if (found)
            {
                fwrite(bytes, sizeof(uint8_t), block, fpt);
            }
        }
    }

    fclose(fpt);
    fclose(input);
}