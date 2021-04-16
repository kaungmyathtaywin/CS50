#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Validate if the user enters key argument
    if (argc == 2)
    {
        // Validate the user types valid key
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]))
            {
                printf("Usage ./caesar key\n");
                return 1;
            }
        }
        // Get plain text from user
        string plain_text = get_string("plaintext: ");
        printf("ciphertext: ");

        for (int i = 0, n = strlen(plain_text); i < n; i++)
        {
            // Print non alphabetical numbers as it is
            if (!isalpha(plain_text[i]))
            {
                printf("%c", plain_text[i]);
            }
            else
            {
                int limit = plain_text[i] + atoi(argv[1]);
                // Starting over from a if new char is greater than z
                while (islower(plain_text[i]) && limit > 122)
                {
                    limit -= 26;
                }
                // Staring over from A if new char is greater than Z
                while (isupper(plain_text[i]) && limit > 90)
                {
                    limit -= 26;
                }
                printf("%c", limit);
            }
        }
        printf("\n");
        return 0;
    }
    else if (argc == 1 || argc > 2)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
}