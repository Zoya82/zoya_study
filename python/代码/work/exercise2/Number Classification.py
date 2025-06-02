num = float(input("请输入一个数字: "))
if num > 0:
    if num % 2 == 0:
        print(f"{num} 是正偶数")
    else:
        print(f"{num} 是正奇数")
elif num < 0:
    if num % 2 == 0:
        print(f"{num} 是负偶数")
    else:
        print(f"{num} 是负奇数")
else:
    print("0既不是正数也不是负数，是偶数")