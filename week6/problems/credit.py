from cs50 import get_string


def main():
    card_number = get_string("Number: ")

    # American express and master card initials
    amex, master = ["34", "37"], ["51", "52", "53", "54", "55"]

    if check(card_number):
        
        # Check visa card 
        if len(card_number) in [13, 16] and card_number[0] == "4":
            print("VISA")
        
        # Check american express
        elif len(card_number) == 15 and card_number[0:2] in amex:
            print("AMEX")
        
        # Check master card
        elif len(card_number) == 16 and card_number[0:2] in master:
            print("MASTERCARD")

        else:
            print("INVALID")

    else:
        print("INVALID")


# Validate credit card number with Luhn's algorithm
def check(number):
    regular, multiplied = 0, 0

    # Regular series starting from last number
    for num in number[len(number) - 1:: -2]:
        regular += int(num)

    # Multiplied series starting from second to last number
    for num in number[len(number) - 2:: -2]:
        product = int(num) * 2

        # Check if the product by 2 is greater than or equal to 10
        if product >= 10:
            multiplied += int(str(product)[0]) + int(str(product)[1])
        else:
            multiplied += product 

    total = regular + multiplied

    # Return true if the last digit of total is 0
    return total % 10 == 0


if __name__ == "__main__":
    main()