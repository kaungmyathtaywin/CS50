#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    // Get number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Letters per 100 words
    float L = (letters * 100) / words;
    // Sentences per 100 words
    float S = (sentences * 100) / words;

    // Coleman-Liau index
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    // Check grades
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

// Calculate number of letters
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Calculate number of words
int count_words(string text)
{
    // Last word ends with a period!
    int words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Find spaces and apostrophe
        if (text[i] == 32 || (text[i] == 39 && text[i - 1] == 73))
        {
            words++;
        }
    }
    return words;
}

// Calculate number of sentences
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Find periods, exclamations and question marks
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}