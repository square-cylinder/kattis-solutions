import random as r
n, q = 7, 4

expression = [str(r.randint(1,9))]
for _ in range(n):
    expression.append(r.choice(['+', '*']))
    expression.append(str(r.randint(1,9)))

print(n+1, q)
print(''.join(expression))

for _ in range(q):
    t = r.randint(1,3)
    if t == 1:
        print('f', r.randint(1,n-1))
    elif t == 2:
        print('s', r.randint(1,n), r.randint(1,n))
    else:
        print('a')
