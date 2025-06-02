light_color = input("请输入交通灯颜色 (red, yellow, green): ").lower()
if light_color == "red":
    print("请停车")
elif light_color == "yellow":
    print("请准备停车")
elif light_color == "green":
    print("请通行")
else:
    print("输入的颜色不正确")