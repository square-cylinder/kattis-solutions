import itertools
import random as r
n = 64
p = 0.5

conn = []
for i, j in itertools.product(range(64), range(64)):
    if i == j: continue
    if r.uniform(0, 1) < p:
        conn.append(f"{i} {j}")

print(f"{n} {len(conn)}")
print("\n".join(conn))
    