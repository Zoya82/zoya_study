def subarray_sum_equals_k(nums, k):
    cum_sum_counts = {0: 1}
    current_cum_sum = 0
    count = 0

    for num in nums:
        current_cum_sum += num

        if current_cum_sum - k in cum_sum_counts:
            count += cum_sum_counts[current_cum_sum - k]

        if current_cum_sum in cum_sum_counts:
            cum_sum_counts[current_cum_sum] += 1
        else:
            cum_sum_counts[current_cum_sum] = 1

    return count


# 示例测试
nums = [1, 1, 1]
k = 2
print(subarray_sum_equals_k(nums, k))  # 输出: 2