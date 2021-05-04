#include <stdio.h>
#include <cs50.h>

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
        // Print spaces
        for (int j = 0; j < space; j++)
        {
            printf(" ");
        }

        // Print hashes
        for (int k = 0; k < hash; k++)
        {
            printf("#");
        }
        printf("\n");

        // Sequence for hash and space
        hash++;
        space--;
    }
}