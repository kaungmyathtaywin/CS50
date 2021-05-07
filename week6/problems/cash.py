from cs50 import get_float
from math import floor


def main():
    # Ask user for positive change owed
    while True:
        dollars = get_float("Change owed: ")
        if dollars > 0:
            break

    cents = round(dollars * 100)

    # Calculate quarters, dimes, nickels and pennies
    quarters, remain = calc(cents, 25)
    dimes, remain = calc(remain, 10)
    nickels, remain = calc(remain, 5)
    pennies, remain = calc(remain, 1)

    # Print total number of coins
    print(quarters + dimes + nickels + pennies)


# Calculate number of change and remaining cash
def calc(total, change):
    coins = floor(total / change)
    remain = total % change

    return coins, remain


if __name__ == "__main__":
    main()