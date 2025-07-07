def coin_change(coins, amount):
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0

    for i in range(1, amount + 1):
        for coin in coins:
            if coin <= i:
                dp[i] = min(dp[i], dp[i - coin] + 1)

    return dp[amount] if dp[amount] != float('inf') else -1


# 示例测试
coins1 = [1, 2, 5]
amount1 = 11
print(coin_change(coins1, amount1))  # 输出: 3

coins2 = [2]
amount2 = 3
print(coin_change(coins2, amount2))  # 输出: -1