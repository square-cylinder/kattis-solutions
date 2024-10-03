import itertools as itt
import functools as ft
import random as r

def main():
    print(1)
    while True:
        x = int(input())
        if 97 <= x <= 98:
            print(99)
        if x % 3 == 0:
            print(x + r.randint(1,2))
        else:
            print(x + 3 - x % 3)
        if x >= 97:
            break


if __name__ == "__main__":
    main()
