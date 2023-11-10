#!/usr/bin/env python3

import random

print(1)
N = 4
print(N, 2)

for i in range(N):
    for j in range(N):
        if i == j:
            continue
        print(chr(ord("a") + i), chr(ord("a") + j), random.randint(2, 50))
