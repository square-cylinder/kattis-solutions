import random as rng
print(5)
stuff = [f"{rng.randint(-10, 10)} {rng.randint(-10, 10)}" for _ in range(3)]
for m in range(1, 6):
    print(f"{len(stuff)} {m}")
    print("\n".join(stuff))
