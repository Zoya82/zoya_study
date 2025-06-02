from collections import Counter, deque


def min_time_to_complete_tasks_optimized(tasks, n):
    task_counts = Counter(tasks)
    time = 0
    total_time = 0
    cooldown_queue = deque(maxlen=n + 1)

    sorted_tasks = sorted(task_counts.items(), key=lambda x: (-x[1], x[0]))

    for task, count in sorted_tasks:
        while count > 0:
            if not cooldown_queue or cooldown_queue[0] != task or time - cooldown_queue.index(task) > n:
                cooldown_queue.append(time)
                count -= 1
                if time + 1 > total_time:
                    total_time = time + 1
                time += 1
            else:
                time += 1

    return total_time


# 示例测试
tasks = ["A", "A", "A", "B", "B", "B"]
n = 2
print(min_time_to_complete_tasks_optimized(tasks, n))