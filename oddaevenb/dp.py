x = int(input())
dp = [[0,0] for _ in range(x+2)]
dp[0][0] = 1
dp[0][1] = 1
MOD = 10**9+7
for i in range(x):
    dp[i+2][0] += dp[i][0]
    if dp[i+2][0] >= MOD:
        dp[i+2][0] -= MOD
    dp[i+1][0] += dp[i][1]
    if dp[i+1][0] >= MOD:
        dp[i+1][0] -= MOD
    dp[i+2][1] += dp[i][0] + dp[i][1]
    while dp[i+2][1] >= MOD:
        dp[i+2][1] -= MOD
print(dp[x][0])