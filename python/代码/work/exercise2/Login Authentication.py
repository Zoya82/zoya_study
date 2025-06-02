correct_username = "admin"
correct_password = "123456"

username = input("请输入用户名: ")
password = input("请输入密码: ")

if username == correct_username and password == correct_password:
    print("登录成功")
else:
    print("用户名或密码错误")