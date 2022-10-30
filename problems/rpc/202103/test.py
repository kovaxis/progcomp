
a = [45, 11, 46, 28, 59, 12, 3, 11, 23, 20]
for i in range(2**10):
    s = 0
    for j in range(10):
        if i & (1 << j) != 0:
            s ^= a[j]
    if s <= 0 and i % 2 == 1:
        for j in range(10):
            if i & (1 << j) != 0:
                print(f"{a[j]} ", end="")
        print()
