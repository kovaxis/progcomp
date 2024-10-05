#!/usr/bin/env python3

import random

N = [100, 80]
for n in N:
    n = int(n)
    print(n, *[random.randint(1, int(50)) for i in range(n)])
