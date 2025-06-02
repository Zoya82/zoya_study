while True:
    try:
        limit = int(input("请输入一个大于1的正整数: "))
        if limit > 1:
            break
        else:
            print("请输入大于1的正整数")
    except ValueError:
        print("输入无效，请输入一个整数")

print(f"1到{limit}之间的质数有: ")
for num in range(2, limit + 1):
    is_prime = True
    for i in range(2, int(num ** 0.5) + 1):
        if num % i == 0:
            is_prime = False
            break
    if is_prime:
        print(num, end=' ')