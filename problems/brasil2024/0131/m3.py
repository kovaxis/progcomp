#!/usr/bin/env python3


def f(x):
    out = 0
    for n in range(len(str(x))):
        out += (x + 9 * 10**n) // (10 ** (n + 1)) * 10**n
        y = x % 10 ** (n + 1)
        if 10**n <= y < 2 * 10**n:
            out -= 2 * 10**n - 1 - y
    return out


K = int(input())

ans = -1
for n1 in range(1, 2):
    for n2 in range(30):
        for n3 in range(1, 300):
            num = int("1" * n1 + "8" * n2 + "1" * n3)
            acc = K * num - f(num)
            if acc < 0:
                if ans == -1 or num < ans:
                    ans = num
print(ans)
exit()

for nines in range(1000):
    num = int("1" * K + "9" * nines + "1")
    acc = K * num - f(num)
    # print(f"acc of {num} = {acc}")
    if acc < 0:
        # print(len(str(num)) - 2)
        print(num)
        break
