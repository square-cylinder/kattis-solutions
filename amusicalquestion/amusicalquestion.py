def main():
    limit, _ = map(int, input().split())
    items = list(map(int, input().split()))

    best = (0,0)
    bestsum = 0
    memo = [[False for _ in range(limit + 1)] for _ in range(limit+1)]
    memo[0][0] = True
    for item in items:
        for sum1 in range(limit, -1, -1):
            for sum2 in range(sum1, -1, -1):
                if not memo[sum1][sum2]:
                    continue
                sum1new = sum1 + item
                if sum1new <= limit:
                    memo[sum1new][sum2] = True
                    if sum1new + sum2 > bestsum or (sum1new + sum2 == bestsum and sum1new - sum2 < best[0] - best[1]):
                        bestsum = sum1new + sum2
                        best = (sum1new, sum2)
                sum2new = sum2 + item
                if sum2new <= limit:
                    if sum2new + sum1 > bestsum or (sum2new + sum1 == bestsum and abs(sum2new - sum1) < best[0] - best[1]):
                        bestsum = sum2new + sum1
                        best = (max(sum1, sum2new), min(sum1, sum2new))
                    if sum2new > sum1:
                        memo[sum2new][sum1] = True
                    else:
                        memo[sum1][sum2new] = True
    print(*best)
    
    


if __name__ == "__main__":
    main()