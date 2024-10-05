#!/usr/bin/env python3

import random

N = 10
K = 2


def gstr():
    while True:
        s = ""
        n = 0
        for i in range(N):
            x = random.randint(0, 1)
            n += x
            s += str(x)
        if n > 0:
            return s


print(N, K)
print(gstr())
