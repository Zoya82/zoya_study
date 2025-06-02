import random

# 生成1到100之间的随机数
secret_number = random.randint(1, 100)
guess = None
while guess != secret_number:
    guess = int(input("请猜一个1到100之间的数字: "))
    if guess < secret_number:
        print("猜的数字小了")
    elif guess > secret_number:
        print("猜的数字大了")

print(f"恭喜！你猜对了，正确数字是 {secret_number}")