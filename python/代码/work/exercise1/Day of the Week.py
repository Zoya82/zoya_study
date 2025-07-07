day_num = int(input("请输入一个1 - 7之间的整数: "))
days = {
    1: "Monday",
    2: "Tuesday",
    3: "Wednesday",
    4: "Thursday",
    5: "Friday",
    6: "Saturday",
    7: "Sunday"
}
if 1 <= day_num <= 7:
    print(days[day_num])
else:
    print("输入的数字不在1 - 7范围内")