import itertools
import random as r
n = 128
p = 0.5

conn = []
for i, j in itertools.product(range(128), range(128)):
    if i == j: continue
    if r.uniform(0, 1) < p:
        conn.append(f"{i+1} {j+1}")

print(f"{n} {len(conn)}")
print("\n".join(conn))
    