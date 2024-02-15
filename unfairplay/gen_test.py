import random as rng


def make_match(N):
    t1 = rng.randint(1, N)
    t2 = rng.randint(1, N)
    while t1 == t2:
        t1 = rng.randint(1, N)
        t2 = rng.randint(1, N)
    return f"{t1} {t2}"


N = rng.randint(5, 50)
M = 5
matches = [make_match(N) for _ in range(M)]

print(f"{N} {M}")
print(" ".join(str(rng.randint(0, 10)) for _ in range(N)))
print("\n".join(matches))

print("\n-1")
