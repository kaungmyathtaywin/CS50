from cs50 import get_string


def main():
    text = get_string("Text: ")

    letters, words, sentences = calc(text)

    # Letters per 100 words
    L = (letters * 100) / words

    # Sentences per 100 words
    S = (sentences * 100) / words

    # Coleman-Liau index
    index = round((0.0588 * L) - (0.296 * S) - 15.8)

    # Check grades
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


# Calculate number of letters, words and sentences
def calc(text):

    letters, sentences = 0, 0

    for char in text:
        if char.isalpha():
            letters += 1
        elif char in [".", "!", "?"]:
            sentences += 1

    words = len(text.split())

    return letters, words, sentences


if __name__ == "__main__":
    main()