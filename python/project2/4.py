def minimumTotal(triangle):
    # 从倒数第二行开始遍历
    for row in range(len(triangle) - 2, -1, -1):
        for col in range(len(triangle[row])):
            # 每个位置的最小路径和等于当前位置的值加上其下面两个位置的较小值
            triangle[row][col] += min(triangle[row + 1][col], triangle[row + 1][col + 1])

    # 最终返回顶部的最小路径和
    return triangle[0][0]

# 示例输入
triangle = [
    [2],
    [3, 4],
    [6, 5, 7],
    [4, 1, 8, 3]
]

# 输出最小路径和
result = minimumTotal(triangle)
print(result)
