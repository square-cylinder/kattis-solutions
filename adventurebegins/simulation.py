import itertools as it
import random as rng

def sim(n_boxes, intervals):
    boxes = [0] * n_boxes
    for u, v in intervals:
        b = rng.randint(u, v)
        boxes[b-1] += 1
    return sum(map(lambda x: x*x, boxes))

n, q = map(int, input().split())
intervals = [(i[1], i[2]) for _ in range(q) if (i := list(map(int, input().split())))[0] == 1]
print("simulating with", n, "boxes and", q, "intervals")
print("intervals are", intervals)
trials = 10**5
mean = 0
for num_done in range(trials):
    mean = mean * (num_done / (num_done + 1)) + sim(n, intervals) / (num_done + 1)
print(mean)
