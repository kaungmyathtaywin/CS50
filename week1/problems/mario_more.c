#include <stdio.h>
#include <cs50.h>

void printChar(string character, int times);

int main(void)
{
    // Ask user for height (1 to 8 inclusive)
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    int hash = 1;
    int space = height - 1;

    for (int i = 0; i < height; i++)
    {
        // Print left pyramid
        printChar(" ", space);
        printChar("#", hash);

        // Gap between two pyramids
        printf("  ");

        // Print right pyramid
        printChar("#", hash);

        // Sequence for hash and space
        hash++;
        space--;

        // Go to next row
        printf("\n");
    }
}

void printChar(string character, int times)
{
    for (int i = 0; i < times; i++)
    {
        printf("%s", character);
    }
}