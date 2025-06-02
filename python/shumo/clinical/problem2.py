import pandas as pd
from datetime import datetime, timedelta
import random
from collections import defaultdict

start_date = "2025-06-01"
end_date = "2025-06-30"
holidays = ["2025-06-01", "2025-06-02",  # 节假日
            "2025-06-14", "2025-06-15",  # 周末
            "2025-06-21", "2025-06-22",  # 周末
            "2025-06-28", "2025-06-29"]  # 周末

staff_db = {
    "1": ["生化组", "检验医师", "男", 6, "正式"],
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

for i in range(8, 29):
    if str(i) not in staff_db:
        group = random.choice(["门诊组", "免疫组", "生化组", "微生物组"])
        if group == "门诊组":
            role = random.choice(["检验医师", "检验技师"])
        else:
            role = random.choice(["检验医师", "高级技师", "中级技师", "初级技师"])
        gender = random.choice(["男", "女"])
        age = random.randint(1, 6)  # 1-6年经验
        staff_db[str(i)] = [group, role, gender, age, "正式"]

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
    global new_staff_counter
    new_staff_counter = 1
    date_range = pd.date_range(start_date, end_date)
    schedule = []
    interns = [f"R{i:02d}" for i in range(1, 11)]

    weekly_counts = defaultdict(int)

    for date in date_range:
        day_str = date.strftime("%Y年%m月%d日")
        day_type = "weekend" if date.weekday() >= 5 or str(date.date()) in holidays else "weekday"
        week_num = date.isocalendar()[1]

        for group in group_shifts.keys():
            if day_type == "weekend":
                staff = select_staff(group, 1, week_num, weekly_counts, require_doctor=True)
                schedule.append([day_str, group, "值班", staff[0], "1"])
            else:
                for shift, count in group_shifts[group].items():
                    staff = select_staff(group, count, week_num, weekly_counts, require_doctor=(count > 1))

                    intern_count = (count + 2) // 3
                    selected_interns = random.sample(interns, intern_count)
                    schedule.append([day_str, group, shift, ",".join(staff), len(selected_interns)])

    return pd.DataFrame(schedule, columns=["日期", "组别", "班次", "人员编号", "实习生数量"])


def select_staff(group, count, week_num, weekly_counts, require_doctor=False):
    global new_staff_counter
    selected = []

    candidates = []
    for id, info in staff_db.items():
        if info[0] == group:  # 同组人员
            if weekly_counts[(id, week_num)] < 4:
                candidates.append(id)

    if require_doctor:
        doctors = [id for id in candidates if staff_db[id][1] == "检验医师"]
        if doctors:
            chosen = random.choice(doctors)
            selected.append(chosen)
            candidates.remove(chosen)
            weekly_counts[(chosen, week_num)] += 1

    while len(selected) < count and candidates:
        weights = [rank_weights[staff_db[id][1]] for id in candidates]
        chosen = random.choices(candidates, weights=weights, k=1)[0]
        selected.append(chosen)
        candidates.remove(chosen)
        weekly_counts[(chosen, week_num)] += 1

    while len(selected) < count:
        new_id = f"S{new_staff_counter:02d}"
        new_staff_counter += 1
        staff_db[new_id] = [group, "高级技师", "男", 3, "新增"]
        selected.append(new_id)
        weekly_counts[(new_id, week_num)] = 1

    return selected

df = generate_schedule()
df.to_excel("检验科6月精细化排班表.xlsx", index=False)

staff_info = [[k] + v for k, v in staff_db.items()]
pd.DataFrame(staff_info, columns=["编号", "组别", "职务", "性别", "年龄", "性质"]) \
    .to_excel("检验科人员详细信息表.xlsx", index=False)
