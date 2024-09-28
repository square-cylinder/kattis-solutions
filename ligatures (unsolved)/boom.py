import random as r

n,q,k = 10 ** 6, 10 ** 5, 1
print(n,q,k)
string = ''.join([r.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(n)])
print(string)
for _ in range(q):
    ligs = ''.join([r.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(k * 2)])
    print(ligs)