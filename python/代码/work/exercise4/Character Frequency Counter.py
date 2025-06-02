string = input("请输入一个字符串: ")
char_freq = {}
for char in string:
    if char in char_freq:
        char_freq[char] += 1
    else:
        char_freq[char] = 1
for char, freq in char_freq.items():
    print(f"字符 '{char}' 出现的频率是 {freq}")