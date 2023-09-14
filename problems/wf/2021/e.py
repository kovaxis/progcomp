#!/usr/bin/env python3

import math

inp = list(map(int, input().split()))
k, m = inp[0:2]
N = inp[2:]
n = sum(N)

K = [0 for i in range(m)]

bigsum = 0.0


def backtrack(i, s):
    global bigsum
    if i == m - 1:
        K[i] = k - s
        for i in range(m):
            if K[i] > N[i]:
                return
        bigsum += math.prod(math.comb(N[i], K[i]) for i in range(m)) * min(
            1, math.factorial(k - 1) * sum(K[i] / (N[i] - K[i] + 1) for i in range(m))
        )
    else:
        for ki in range(k - s + 1):
            K[i] = ki
            backtrack(i + 1, s + ki)


backtrack(0, 0)
ans = bigsum / math.comb(n, k)

print(f"{ans:0.12f}")
