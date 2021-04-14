#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get user name and print it
    string name = get_string("What' your name? ");
    printf("hello, %s\n", name);
}