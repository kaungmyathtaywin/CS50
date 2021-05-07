from cs50 import get_int


def main():
    height = get_height()

    # Print pyramid
    for i in range(1, height + 1):
        build(" ", height - i)
        build("#", i)
        print()


# Get height from user between 1 and 8 inclusive
def get_height():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n


# Print characters n times in one line
def build(char, n):
    for i in range(n):
        print(char, end="")


if __name__ == "__main__":
    main()