
import math
import random as rng
def fst(t):
    return t[0]

def snd(t):
    return t[1]

n = int(input())
coords = [tuple(map(int,input().split())) for _ in range(n)]
leastx = min(map(fst, coords))
mostx = max(map(fst, coords))
leasty = min(map(snd, coords))
mosty = max(map(snd, coords))
best = 1e9
bestx = -1
besty = -1
for _ in range(1000000):
    x = rng.uniform(leastx, mostx)
    y = rng.uniform(leasty, mosty)
    tot = sum(map(lambda p: math.hypot(x-p[0], y-p[1]), coords))
    if tot < best:
        best = tot
        bestx = x
        besty = y
print(f"best position was ({bestx}, {besty}) with a total distance of {best}")