#include <stdio.h>
#include <cs50.h>

void draw(int h);

int main(void)
{   
    // Get height from user
    int height = get_int("Height: ");

    draw(height);
}

void draw(int h)
{
    // If nothing to draw
    if (h == 0)
    {
        return;
    }
    // Draw Pyramid of height h - 1
    draw(h - 1);
    // Draw one more row of width h
    for (int i = 0; i < h; i++)
    {
        printf("#");
    }
    printf("\n");
}