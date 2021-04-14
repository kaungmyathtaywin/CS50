#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start_size, end_size;

    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // Prompt for end size
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // Calculate number of years
    int years = 0;

    while (start_size < end_size)
    {
        // Growth per each year
        start_size = start_size + start_size / 3 - start_size / 4;
        years++;
    }

    printf("Years: %i\n", years);
}
