def max_area(height):
    left, right = 0, len(height) - 1
    max_water = 0

    while left < right:
        width = right - left
        current_water = min(height[left], height[right]) * width
        max_water = max(max_water, current_water)

        if height[left] < height[right]:
            left += 1
        else:
            right -= 1

    return max_water


height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
print("最大容器的容量为:", max_area(height))
