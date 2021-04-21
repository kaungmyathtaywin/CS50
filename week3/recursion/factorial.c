#include <stdio.h>
#include <cs50.h>

int factorial(int n);

int main(void)
{   
    int n = get_int("Enter a number: ");
    printf("Factorial of %i: %i\n", n, factorial(n));
}

int factorial(int n)
{
    // base case 
    if (n == 1)  return 1;
    // recursive case
    return n * factorial(n - 1);
}