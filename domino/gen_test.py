import random
n = 50
k = 8

print(f"{n} {k}")
for _ in range(n):
    for _ in range(n):
        print(random.randint(0, 50), end=" ")
    print()
