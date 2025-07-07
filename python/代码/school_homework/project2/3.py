def solveNQueens(n):
    def is_valid(board, row, col):
        # 检查当前列是否有皇后
        for i in range(row):
            if board[i] == col or abs(board[i] - col) == abs(i - row):
                return False
        return True

    def backtrack(row):
        # 如果已放置完n个皇后
        if row == n:
            # 将当前解转化为棋盘形式并保存
            result.append(["." * i + "Q" + "." * (n - i - 1) for i in board])
            return
        for col in range(n):
            if is_valid(board, row, col):
                board[row] = col  # 放置皇后
                backtrack(row + 1)  # 尝试放置下一行的皇后
                board[row] = -1  # 回溯，移除皇后

    result = []
    board = [-1] * n  # 使用列表来记录每行皇后的列号
    backtrack(0)
    return result


# 示例输入：n = 4
n = 4
solutions = solveNQueens(n)
print(f"解法数：{len(solutions)}")
for solution in solutions:
    for row in solution:
        print(row)
    print()
