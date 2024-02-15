from collections import deque
import sys
#sys.stdin = open("/home/hugo/dev/competetive_programming/escapewallmaria/samples/test0.in")

def main():
    t,n,m =map(int, input().split())
    rows = [input() for _ in range(n)]
    for i in range(n):
        for j in range(m):
            if (rows[i][j] == 'S'):
                start = (i,j)
                break
    visited = set()
    bfs = deque()
    bfs.append((0, *start))
    while len(bfs) > 0:
        d, y, x = bfs.popleft()
        if y == 0 or x == 0 or y == n - 1 or x == m - 1:
            print(d)
            return
        if d >= t:
            continue
        if (y,x) in visited:
            continue
        visited.add((y,x))
        for i, (dx, dy) in enumerate(((0,-1),(-1,0),(0,1),(1,0))):
            nx, ny = x + dx, y + dy
            if 0 <= nx < m and 0 <= ny < n:
                c = rows[ny][nx]
                if (ny,nx) in visited or (c in "DRUL1" and  "DRUL1".index(c) != i):
                    continue
                bfs.append((d + 1, ny,nx))
    print("NOT POSSIBLE")
    


if __name__ == "__main__":
    main()
