#include <stdio.h>
#include <cs50.h>
#include <math.h>

int add_coins(int total, int change);

int main(void)
{
    float dollars;
    // Ask user for change owed
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);

    int coins = 0;
    int cents = round(dollars * 100);
    int quarter = 25, dime = 10, nickle = 5, penny = 1;

    // Add quarters and update total
    int quarters = add_coins(cents, quarter);
    cents = cents - (quarters * quarter);

    // Add dimes and update total
    int dimes = add_coins(cents, dime);
    cents = cents - (dimes * dime);

    // Add nickles and update total
    int nickles = add_coins(cents, nickle);
    cents = cents - (nickles * nickle);

    // Add pennies
    int pennies = add_coins(cents, penny);

    coins = quarters + dimes + nickles + pennies;

    printf("%i\n", coins);
}

int add_coins(int total, int change)
{
    int coins = 0;

    while (total >= change)
    {
        total -= change;
        coins++;
    }

    return coins;
}