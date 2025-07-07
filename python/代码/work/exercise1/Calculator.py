num1 = float(input("请输入第一个数: "))
num2 = float(input("请输入第二个数: "))
op = input("请输入运算符 (+, -, *, /): ")
if op == '+':
    result = num1 + num2
elif op == '-':
    result = num1 - num2
elif op == '*':
    result = num1 * num2
elif op == '/':
    if num2 != 0:
        result = num1 / num2
    else:
        print("除数不能为0")
        result = None
if result is not None:
    print(f"{num1} {op} {num2} = {result}")