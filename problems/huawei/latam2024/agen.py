#!/usr/bin/env python3

import random

n = 15
m = 7
print(m)
seen = set()
for j in range(m):
    while True:
        u = random.randint(0, n - 1)
        v = random.randint(0, n - 1)
        if v == u:
            continue
        if (u, v) in seen:
            continue
        break
    print(u, v)
    seen.add((u, v))
    seen.add((v, u))
