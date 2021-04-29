#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

bool check_duplicate(string text);

int main(int argc, string argv[])
{
    // Validate if the user enters key argument
    if (argc != 2)
    {
        printf("Usage ./substituition key\n");
        return 1;
    }

    // Validate if the key contains 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Handles non alphabetical characters in key
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        char c = argv[1][i];
        if (!isalpha(c))
        {
            printf("Key must only be alphabets.\n");
            return 1;
        }
    }

    // Handles duplicate characters in key
    if (check_duplicate(argv[1]) == true)
    {
        printf("Key must not contain duplicate characters.\n");
        return 1;
    }

    // Get plaintext and key from the user
    string key = argv[1];
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];
        // Print non alphabetical characters
        if (!isalpha(c))
        {
            printf("%c", c);
        }
        else
        {
            // Encrypt uppercase characters
            if (isupper(c))
            {
                printf("%c", toupper(key[c - 65]));
            }
            // Encrypt lowercase characters
            else
            {
                printf("%c", tolower(key[c - 97]));
            }
        }
    }
    printf("\n");
    return 0;
}

bool check_duplicate(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int k = strlen(text) - 1;

        for (int j = i + 1; j < k; j++)
        {
            int diff = tolower(text[i]) - toupper(text[j]);

            // Handles duplicate characters case sensitive
            if (text[i] == text[j] || diff == 32)
            {
                return true;
            }
        }
        // Subtract number of chars to check against i
        k--;
    }
    return false;
}