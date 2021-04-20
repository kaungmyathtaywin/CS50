#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void)
{
    int n = get_int("Number: ");
    printf("Steps: %i\n", collatz(n));
}

int collatz(int n)
{
    // base case
    if (n == 1) return 0;
    // even numbers
    else if (n % 2 == 0) return collatz(n / 2) + 1;
    // odd numbers
    else return collatz(3*n + 1) + 1;
}