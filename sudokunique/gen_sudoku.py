import random

random.uniform(0, 1)

def gen_board(p):
    return [[0 if random.uniform(0,1) < p else random.randint(1, 9) for _ in range(9)] for _ in range(9)]

for _ in range(100):
    print("\n".join(" ".join(map(str, r)) for r in gen_board(0.3)))
    print()