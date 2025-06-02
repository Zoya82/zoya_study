num = int(input("请输入一个整数: "))
factorial = 1
for i in range(1, num + 1):
    factorial *= i
print(f"{num} 的阶乘是 {factorial}")