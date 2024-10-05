#!/usr/bin/env python3

import random

N = int(1e6)
M = int(1e18)
K = 1
print(N, M, K)
print(" ".join(str(random.randint(0, M)) for i in range(N)))
