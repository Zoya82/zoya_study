import pulp

# 物品的名称
items = [
    '创可贴', '最好的绷带', '信号弹', '毯子', '胶带', '冷敷包',
    '晒斑霜', '消毒膏', '退热净胶囊', '橡皮手套'
]

# 物品的成本（元/单位）
costs = {
    '创可贴': 5.00,
    '最好的绷带': 10.00,
    '信号弹': 20.00,
    '毯子': 75.00,
    '胶带': 12.50,
    '冷敷包': 10.00,
    '晒斑霜': 17.50,
    '消毒膏': 10.00,
    '退热净胶囊': 7.50,
    '橡皮手套': 7.50
}

# 每种物品的基本单位重量（斤）
weights = {
    '创可贴': 0.2,
    '最好的绷带': 0.2,
    '信号弹': 1.0,
    '毯子': 2.0,
    '胶带': 0.4,
    '冷敷包': 0.8,
    '晒斑霜': 0.4,
    '消毒膏': 0.5,
    '退热净胶囊': 0.3,
    '橡皮手套': 0.2
}

# 急救包类型和需求量
demand = {
    '汽车': 1000,
    '徒步旅行者': 800,
    '野营者': 100,
    '运动员': 200,
    '勘探队': 300
}

# 每种急救包的物品需求量
requirements = {
    '汽车': {'最好的绷带': 1, '创可贴': 0, '信号弹': 2, '毯子': 1, '胶带': 2, '冷敷包': 2, '晒斑霜': 1, '消毒膏': 1, '退热净胶囊': 1, '橡皮手套': 1},
    '徒步旅行者': {'最好的绷带': 2, '创可贴': 2, '信号弹': 1, '毯子': 1, '胶带': 2, '冷敷包': 2, '晒斑霜': 2, '消毒膏': 2, '退热净胶囊': 2, '橡皮手套': 1},
    '野营者': {'最好的绷带': 4, '创可贴': 4, '信号弹': 1, '毯子': 4, '胶带': 3, '冷敷包': 3, '晒斑霜': 4, '消毒膏': 3, '退热净胶囊': 4, '橡皮手套': 2},
    '运动员': {'最好的绷带': 12, '创可贴': 4, '信号弹': 0, '毯子': 2, '胶带': 6, '冷敷包': 6, '晒斑霜': 4, '消毒膏': 2, '退热净胶囊': 6, '橡皮手套': 10},
    '勘探队': {'最好的绷带': 6, '创可贴': 4, '信号弹': 2, '毯子': 3, '胶带': 4, '冷敷包': 3, '晒斑霜': 5, '消毒膏': 4, '退热净胶囊': 6, '橡皮手套': 5}
}

# 创建优化问题
problem = pulp.LpProblem("First_Aid_Kit_Optimization", pulp.LpMinimize)

# 定义决策变量
item_vars = pulp.LpVariable.dicts("Item", items, lowBound=0, cat='Integer')

# 目标函数：最小化总成本
problem += pulp.lpSum([item_vars[item] * costs[item] for item in items])

# 计算每种物品的总需求
total_demands = {item: 0 for item in items}
for package_type in demand:
    for item in items:
        required_quantity = requirements[package_type].get(item, 0)
        total_demands[item] += required_quantity * demand[package_type]

# 约束条件：满足每种物品的总需求
for item in items:
    problem += item_vars[item] >= total_demands[item], f"Min_{item}"

# 求解问题
problem.solve()

# 输出结果
if pulp.LpStatus[problem.status] == "Optimal":
    print("最优解:")
    for item in items:
        print(f"{item}: {item_vars[item].varValue} 个")
    print(f"总成本: {pulp.value(problem.objective)} 元")
else:
    print("没有找到最优解")