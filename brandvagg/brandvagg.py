import itertools as itt
import functools as ft
from collections import defaultdict

IP = 0
PORT = 1
LIMIT = 2

ACCEPT = 0
DROP = 1
LOG = 2

def main():
    rules = []
    for _ in range(int(input())):
        stuff = input().split()
        action = ["accept", "drop", "log"].index(stuff[0])
        conditions = []
        for a, b in map(lambda x: x.split('='), stuff[1:]):
            condition = ["ip", "port", "limit"].index(a)
            if condition != IP:
               conditions.append((condition, int(b)))
            else:
                conditions.append((condition, b))
        rules.append((action, conditions))
    
    howmany = defaultdict(int)
    packets = []
    for packet in range(1, 1 + int(input())):
        ip, port = input().split(':')
        port = int(port)
        packets.append((packet, ip, port))
        howmany[ip] += 1
        if len(packets) > 1000:
            howmany[packets[-1001][1]] -= 1
        
        def check(rule):
            condition, value = rule
            if condition == IP:
                return value == ip
            if condition == PORT:
                return value == port
            if condition == LIMIT:
                return howmany[ip] >= value
        
        for action, conditions in rules:
            if all(map(check, conditions)):
                if action == ACCEPT:
                    print(f"accept {packet}")
                    break
                elif action == DROP:
                    print(f"drop {packet}")
                    break
                elif action == LOG:
                    print(f"log {packet}")


if __name__ == "__main__":
    main()
