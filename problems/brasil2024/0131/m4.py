#!/usr/bin/env python3


def f(x):
    out = 0
    for n in range(len(str(x))):
        out += (x + 9 * 10**n) // (10 ** (n + 1)) * 10**n
        y = x % 10 ** (n + 1)
        if 10**n <= y < 2 * 10**n:
            out -= 2 * 10**n - 1 - y
    return out


K, N = map(int, input().split())
print(K * N - f(N))
