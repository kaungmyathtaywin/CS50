#include <stdio.h>
#include <cs50.h>
#include <math.h>

long multiplied_addition(long card_number);
long regular_addition(long card_number);
int get_number_of_digits(long card_number);

int main(void)
{
    long card_number = get_long("Number: ");

    // Get two addition sequenes and number of digits
    int first_sequence = multiplied_addition(card_number);
    int second_sequence = regular_addition(card_number);
    int digits = get_number_of_digits(card_number);

    // Get first and second digits for validation
    int first_digit = card_number / (long) pow(10, digits - 1);
    int first_two_digits = card_number / (long) pow(10, digits - 2);

    int total = first_sequence + second_sequence;

    // Check Luhn's algorithm
    if (total % 10 == 0)
    {   
        // Visa validation
        if ((digits == 13 || digits == 16) && (first_digit == 4))
        {
            printf("VISA\n");
        }
        // American express validation
        else if ((digits == 15) && (first_two_digits == 34 || first_two_digits == 37))
        {
            printf("AMEX\n");
        }
        // Master validation
        else if (digits == 16)
        {
            // Check Master card multiple two digits possibilities
            switch (first_two_digits)
            {
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    printf("MASTERCARD\n");
                    break;
                default:
                    printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// Calculate first sequence of Luhn's algorithm
long multiplied_addition(long card_number)
{
    long divisor = 10;
    long addition = 0;
    long number = card_number;
    
    // Adding digits from second to last 
    while (card_number > 1)
    {
        long digit_to_add = (number / divisor) % 10;
        
        // Check multiplied by 2 number is greater than 10 
        if (digit_to_add * 2 < 10)
        {
            addition += (digit_to_add * 2);
        }
        else
        {
            // Split tens and units digits
            long large_number = digit_to_add * 2;
            long unit_digit = large_number % 10;
            long tens_digit = (large_number / 10) % 10;
            addition += unit_digit + tens_digit;
        }
        // Update divisor and card number
        divisor *= 100;
        card_number /= 100;
    }
    return addition;
}

// Calculate second sequence of Luhn's algorithm
long regular_addition(long card_number)
{
    long divisor = 1;
    long addition = 0;
    long number = card_number;
    
    // Adding digits from last digit
    while (card_number > 1)
    {
        long digit_to_add = (number / divisor) % 10;
        addition += digit_to_add;
        divisor *= 100;
        card_number /= 100;
    }
    return addition;
}

// Calculate the number of digits in card number
int get_number_of_digits(long card_number)
{
    int number = 0;
    while (card_number > 1)
    {
        card_number /= 10;
        number++;
    }
    return number;
}