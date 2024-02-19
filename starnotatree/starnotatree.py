from math import *

# Final submission, gradient descent with decreasing step size

def main():
    n = int(input())
    coords = [tuple(map(int,input().split())) for _ in range(n)]
    def deriv(x, y):
        def thething(x, xi, y, yi):
            if (x - xi) == 0:
                return 0
            return (x - xi) / sqrt((x-xi)**2 + (y - yi) ** 2)
        xd = 0
        yd = 0
        for i in range(len(coords)):
            xi, yi = coords[i]
            xd += thething(x, xi, y, yi)
            yd += thething(y, yi, x, xi)
        return (xd, yd)
    x = sum(map(lambda p: p[0], coords)) / n
    y = sum(map(lambda p: p[1], coords)) / n
    ITERATIONS = 100000
    for v in range(ITERATIONS):
        xd, yd = deriv(x,y)
        x -= xd * 100 * (ITERATIONS - v) / ITERATIONS
        y -= yd * 100 * (ITERATIONS - v) / ITERATIONS
    print(sum(map(lambda p: hypot(p[0] - x, p[1] - y), coords)))


if __name__ == "__main__":
    main()
