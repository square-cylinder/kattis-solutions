
inf = 9999999999

for _ in range(int(input())):
    n = int(input())
    heights = [int(i) for i in input().split()]
    memo = dict()
    def solve(i, h):
        if h < 0:
            return (inf, "")

        if i >= len(heights):
            if h == 0:
                return (0, "")
            else:
                return (inf, "")

        if (i, h) in memo:
            return memo[(i,h)]

        up = h + heights[i]
        down = h - heights[i]

        upthing = solve(i+1, up)
        downthing = solve(i+1, down)
        bestup = max(upthing[0], h)
        bestdown = max(downthing[0], h)

        if bestup < bestdown:
            memo[(i,h)] = (bestup, "U" + upthing[1])
        else:
            memo[(i,h)] = (bestdown, "D" + downthing[1])
        return memo[(i,h)]

    if solve(0, 0)[0] == inf:
        print("IMPOSSIBLE")
    else:
        print(solve(0, 0)[1])



        