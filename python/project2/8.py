def sort_colors(nums):
    low, mid, high = 0, 0, len(nums) - 1

    while mid <= high:
        if nums[mid] == 0:
            nums[low], nums[mid] = nums[mid], nums[low]
            low += 1
            mid += 1
        elif nums[mid] == 1:
            mid += 1
        else:
            nums[mid], nums[high] = nums[high], nums[mid]
            high -= 1


# 示例测试
nums = [2, 0, 2, 1, 1, 0]
sort_colors(nums)
print(nums)  # 输出应为: [0, 0, 1, 1, 2, 2]