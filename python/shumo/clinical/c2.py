import numpy as np
from scipy.optimize import minimize

# 定义每月标本数和总收入数据（示例数据，替换为实际数据）
months = {
    '标本数': [11957, 13066, 19607, 14608, 16579, 14618, 13976, 13916, 13743, 13842, 12259, 12515],
    '总收入': [741790, 628135, 1113670, 752810, 877650, 771250, 717200, 686810, 705550, 713250, 608170, 764390]
}

# 定义方程函数和优化目标
def equations(vars, num_samples, total_income):
    x, y, z, a, b, c, d, e, f, g = vars
    a=18*(e+f+z+x+g)
    # 标本数方程
    eq1 = 3*x + y + 2*z + g + e + 2*f + b + c + d - num_samples
    # 总收入方程
    term1 = 700*x + 145*y + 387.5*z  + 35*g + 130*b + 29*c + 30*d + 44.5*e + 38*f
    term2 = ((x + b)/100) * 20
    term3 = ((e + f + z + x + g)/100) * (1900 + 6800)
    term4 = ((e + f + z + x + g)/1000) * (850 + 450 * 3)
    term5 = ((c + z)/1000) * (680 + 700)
    term6 = (x/1000) * (3240 + 2300 + 1800)
    term7 = 20*(x+y+z+b+e+f+g)
    term8 =18*(e+f+z+x+g)
    income_calculated = term1 + term2 + term3 + term4 + term5 + term6+ term7+term8
    eq2 = income_calculated - total_income
    # 返回误差平方和
    return eq1**2 + eq2**2

# 初始化变量范围（假设变量非负）
bounds = [(0, None)] * 10

# 遍历每个月进行优化
results = {}
for i in range(12):
    num_samples = months['标本数'][i]
    total_income = months['总收入'][i]
    # 初始猜测值（可调整）
    initial_guess = np.ones(10)
    # 优化求解
    res = minimize(equations, initial_guess, args=(num_samples, total_income),
                  method='SLSQP', bounds=bounds)
    results[f'Month {i+1}'] = res.x

# 输出结果（示例）
for month, vars in results.items():
    print(f"{month}:")
    print(f"x={vars[0]:.1f}, y={vars[1]:.1f}, z={vars[2]:.1f}, a={vars[3]:.1f}, b={vars[4]:.1f}, "
          f"c={vars[5]:.1f}, d={vars[6]:.1f}, e={vars[7]:.1f}, f={vars[8]:.1f}, g={vars[9]:.1f}\n")