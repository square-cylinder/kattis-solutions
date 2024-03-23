import itertools as itt
import functools as ft
import math

"""
1: a
2: bb
3: aaa, abb, bba
4: bbbb, abba
5: aaaaa, bbaaa, aaabb, abbbb, bbabb, bbbba
6: bbbbbb, abbbba, aaabba, abbaaa, abbabb, bbabba
"""

MOD = 10 ** 9 + 7

def main():
    x = int(input())
    num_sol = 0
    for num_groups in itt.count(0):
        max_avail_bs = x - num_groups
        if max_avail_bs < 2 * (num_groups - 1):
            break
        if num_groups == 0:
            num_sol += int(x % 2 == 0)
            continue
        if num_groups == 1 and x % 2 == 0:
            continue
        #print(f"trying {num_groups} groups")
        for num_a in itt.count(num_groups):
            if num_a > x:
                break
            if (num_a - num_groups) % 2 != 0:
                continue
            avail_b = x - num_a
            if avail_b % 2 != 0:
                continue
            avail_b_groups = avail_b // 2
            if avail_b_groups < num_groups - 1:
                break
            # 1 a in each group to start
            rem_a = num_a - num_groups
            assert rem_a % 2 == 0
            num_2groups_a = rem_a // 2
            num_config_a = math.comb(num_2groups_a + num_groups - 1, num_groups - 1) % MOD
            rem_b_groups = avail_b_groups - (num_groups - 1)
            num_config_b = math.comb(rem_b_groups + num_groups, num_groups) % MOD
            #print(f"{num_config_a * num_config_b} combinations for {num_groups} groups with {num_a} a's and {avail_b} b's")
            #print(f"{rem_b_groups = }")
            num_sol = (num_sol + num_config_a * num_config_b) % MOD
    print(num_sol)

            





if __name__ == "__main__":
    main()
