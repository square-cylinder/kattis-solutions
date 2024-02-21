import random as rng

n = rng.randint(10,40)

print(n)
for i in range(1, n):
    a = rng.randint(1,i)
    b = i+1
    print(a,b)

x = y = -1
while x == y:
    x, y = rng.randint(1,n), rng.randint(1,n)
print(x,y) 

