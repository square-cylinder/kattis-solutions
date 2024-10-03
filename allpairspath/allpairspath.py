import itertools as itt
import functools as ft

INF = 2 ** 31 - 1
MINF = -(2 ** 31)


def floydwarshall(n, mat):
    can_traverse = lambda t: mat[t[1]][t[0]] < INF and mat[t[0]][t[2]] < INF
    for k, i, j in filter(can_traverse, itt.product(range(n), repeat=3)):
        if mat[i][k] + mat[k][j] < mat[i][j]:
            mat[i][j] = mat[i][k] + mat[k][j]
            if i == j:
                mat[i][i] = max(-1, mat[i][i])

    for i, u, v in filter(can_traverse, itt.product(filter(lambda i: mat[i][i] < 0, range(n)), range(n), range(n))):
        mat[u][v] = MINF


def solve(n, m, q):
    mat = [[INF for _ in range(n)] for _ in range(n)]

    for i in range(n):
        mat[i][i] = 0

    for _ in range(m):
        u, v, w = map(int, input().split())
        mat[u][v] = min(w, mat[u][v])

    floydwarshall(n, mat)
    for _ in range(q):
        u, v = map(int, input().split())
        if mat[u][v] == INF:
            print("Impossible")
        elif mat[u][v] == MINF:
            print("-Infinity")
        else:
            print(mat[u][v])

    

def main():
    while True:
        n, m, q = map(int, input().split())
        if n == 0 and m == 0 and q == 0:
            break
        solve(n, m, q)
        print()


if __name__ == "__main__":
    main()
