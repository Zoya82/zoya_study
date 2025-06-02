side1 = float(input("请输入第一条边的长度: "))
side2 = float(input("请输入第二条边的长度: "))
side3 = float(input("请输入第三条边的长度: "))

if side1 == side2 == side3:
    print("这是等边三角形")
elif side1 == side2 or side1 == side3 or side2 == side3:
    print("这是等腰三角形")
else:
    print("这是不等边三角形")