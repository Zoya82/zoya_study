import sqlite3

# 连接到 SQLite 数据库
conn = sqlite3.connect('D:\pycharm/video_player_last_version_1/video_player/instance/mv.db')
cursor = conn.cursor()

# 查看所有表
cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
tables = cursor.fetchall()
print("数据库中的表：", tables)

# 查看表结构
for table in tables:
    table_name = table[0]
    print(f"\n表名: {table_name}")
    cursor.execute(f"PRAGMA table_info({table_name});")
    columns = cursor.fetchall()
    print("列信息：", columns)

    # 查看表中的数据
    cursor.execute(f"SELECT * FROM {table_name};")
    rows = cursor.fetchall()
    print("数据：", rows)

# 关闭连接
conn.close()