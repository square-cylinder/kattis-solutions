a = int(input())
c2 = a & 15
c1 = (a>>4) & 15
r2 = (a>>8) & 3
r1 = (a>>10) & 3
it = a>>12

print(f"{(r1, c1) = }, {(r2, c2) = }, {it = }")