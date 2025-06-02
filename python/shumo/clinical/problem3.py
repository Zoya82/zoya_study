import pandas as pd
from datetime import datetime, timedelta
import random
from collections import defaultdict
import math

# === 参数配置 === #
start_date = "2025-06-01"
end_date = "2025-06-30"
holidays = ["2025-06-01", "2025-06-02",  # 节假日
            "2025-06-14", "2025-06-15",
            "2025-06-21", "2025-06-22",
            "2025-06-28", "2025-06-29"]

# 人员数据库（简化）
staff_db = {
    "1": ["生化组", "检验医师", "女", 6, "正式"],
    "2": ["门诊组", "检验医师", "女", 5, "正式"],
    "3": ["生化组", "检验医师", "女", 6, "正式"],
    "4": ["门诊组", "检验技师", "男", 1, "正式"],
    "5": ["生化组", "检验医师", "女", 2, "正式"],
    "6": ["微生物组", "检验技师", "女", 1, "正式"],
    "7": ["免疫组", "检验医师", "女", 2, "正式"],
    "8": ["门诊组", "检验技师", "女", 3, "正式"],
    "9": ["生化组", "检验医师", "女", 6, "正式"],
    "10": ["门诊组", "检验技师", "女", 2, "正式"],
    "11": ["微生物组", "检验技师", "女", 3, "正式"],
    "12": ["免疫组", "检验医师", "男", 3, "正式"],
    "13": ["免疫组", "检验医师", "女", 3, "正式"],
    "14": ["生化组", "检验医师", "女", 2, "正式"],
    "15": ["门诊组", "检验医师", "女", 2, "正式"],
    "16": ["微生物组", "检验技师", "女", 2, "正式"],
    "17": ["生化组", "检验技师", "女", 3, "正式"],
    "18": ["微生物组", "检验医师", "女", 6, "正式"],
    "19": ["免疫组", "检验医师", "女", 2, "正式"],
    "20": ["门诊组", "检验医师", "女", 5, "正式"],
    "21": ["微生物组", "检验医师", "女", 3, "正式"],
    "22": ["门诊组", "检验技师", "女", 1, "正式"],
    "23": ["生化组", "检验医师", "女", 1, "正式"],
    "24": ["免疫组", "检验技师", "女", 2, "正式"],
    "25": ["门诊组", "检验技师", "女", 2, "正式"],
    "26": ["门诊组", "检验技师", "女", 1, "正式"],
    "27": ["免疫组", "检验技师", "女", 2, "正式"]
}

# 模拟3人休产假（可调整）
maternity_leave_ids = ["2", "7", "15"]
for i in maternity_leave_ids:
    staff_db.pop(i, None)

rank_weights = {
    "检验医师": 1.2,
    "高级技师": 1.1,
    "中级技师": 1.0,
    "初级技师": 0.9,
    "检验技师": 1.0
}

group_shifts = {
    "门诊组": {"早班": 3, "中班": 3, "晚班": 2},
    "免疫组": {"早班": 4, "中班": 3},
    "生化组": {"早班": 3, "中班": 3},
    "微生物组": {"早班": 2, "中班": 2}
}

def generate_schedule():
    date_range = pd.date_range(start_date, end_date)
    schedule = []
    weekly_counts = defaultdict(int)
    new_staff_counter = 1

    for date in date_range:
        day_str = date.strftime("%Y年%m月%d日")
        day_type = "weekend" if date.weekday() >= 5 or str(date.date()) in holidays else "weekday"
        week_num = date.isocalendar()[1]

        for group, shifts in group_shifts.items():
            if day_type == "weekend":
                staff = select_staff(group, 1, week_num, weekly_counts, True)
                schedule.append([day_str, group, "值班", staff[0], 1])
            else:
                for shift, count in shifts.items():
                    staff = select_staff(group, count, week_num, weekly_counts, count > 1)
                    intern_count = math.ceil(count / 3)
                    schedule.append([day_str, group, shift, ",".join(staff), intern_count])

    return pd.DataFrame(schedule, columns=["日期", "组别", "班次", "人员编号", "实习生数量"])

def select_staff(group, count, week_num, weekly_counts, require_doctor):
    selected = []
    candidates = [id for id, info in staff_db.items() if info[0] == group and weekly_counts[(id, week_num)] < 4]
    if require_doctor:
        doctors = [id for id in candidates if staff_db[id][1] == "检验医师"]
        if doctors:
            chosen = random.choice(doctors)
            selected.append(chosen)
            candidates.remove(chosen)
            weekly_counts[(chosen, week_num)] += 1

    while len(selected) < count and candidates:
        weights = [rank_weights[staff_db[id][1]] for id in candidates]
        chosen = random.choices(candidates, weights=weights)[0]
        selected.append(chosen)
        candidates.remove(chosen)
        weekly_counts[(chosen, week_num)] += 1

    while len(selected) < count:
        new_id = f"S{len(staff_db)+1:02d}"
        staff_db[new_id] = [group, "高级技师", "男", 3, "新增"]
        selected.append(new_id)
        weekly_counts[(new_id, week_num)] =

    return selected

# === 执行 === #
df = generate_schedule()
df.to_excel("2025年6月（考虑产假）检验科排班表.xlsx", index=False)
print("排班表已生成：2025年6月检验科排班表.xlsx")
