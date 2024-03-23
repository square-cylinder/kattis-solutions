import itertools as it

def value(expr):
    return eval(''.join(expr))

def flip(expr, index):
    index = index * 2 + 1
    if (expr[index] == '+'):
        expr[index] = '*'
    else:
        expr[index] = '+'

def solve():
    num_ints, num_queries = map(int, input().split())
    expr = list(input())
    print(value(expr))
    for _ in range(num_queries):
        line = input().split()
        if line[0] == 'f':
            flip(expr, int(line[1]) - 1)
        elif line[0] == 's':
            i, j = map(int, line[1:])
            i -= 1
            j -= 1
            tmp = expr[i*2]
            expr[i*2] = expr[j*2]
            expr[j*2] = tmp
        else:
            for i in it.count():
                if i * 2 + 1 >= len(expr):
                    break
                flip(expr, i)
        print(value(expr) % 1000000007)

solve()
    