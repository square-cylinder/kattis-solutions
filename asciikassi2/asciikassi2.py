import itertools as itt
import functools as ft

def main():
    sz = int(input())
    segs = [" " * (sz + 1) + "x"]
    for i in range(sz):
        x = sz-i
        segs.append(" " * x + "/" + " " * (2*i+1) + "\\")
    segs.append("x" + " " * (2*sz+1) + "x")
    for i in range(sz):
        x = i + 1
        segs.append(" " * x + "\\" + " " * (2*(sz-i-1)+1) + "/")
    segs.append(" " * (sz + 1) + "x")
    print("\n".join(segs))



if __name__ == "__main__":
    main()
