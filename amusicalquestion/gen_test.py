import random as rng
c = 500
n = 500
songs = [str(rng.randint(1, 1000)) for _ in range(n)]
print(c,n)
print(" ".join(songs))