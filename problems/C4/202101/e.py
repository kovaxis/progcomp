
input()
nums = input().split(' ')
for num in nums:
    num = int(num)
    mod = num % 14
    if num > 14 and mod >= 1 and mod <= 6:
        print("YES")
    else:
        print("NO")
