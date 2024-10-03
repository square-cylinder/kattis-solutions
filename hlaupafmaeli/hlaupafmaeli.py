import itertools as itt
import functools as ft

def main():
    bday = int(input())
    # For every four hundred years after 2400,
    # she will celebrate 100 - 4 + 1 = 97 bdays
    # At year 2400 she will have celebrated 97 - 5 = 92 bdays
    # she misses the birthdays {2000, 2004, 2008, 2012, 2016}
    if bday % 4 != 0 or (bday % 100 == 0 and bday % 400 != 0):
        print("Neibb")
    else:
        a = bday - 2000
        fourhundredthing = a // 400
        total = fourhundredthing * 97
        a -= fourhundredthing * 400
        if a > 0:
            total += a // 4 - a // 100
        print(total - 5)



if __name__ == "__main__":
    main()
