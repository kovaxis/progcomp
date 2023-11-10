#!/usr/bin/env python3

import random

W, H = 20, 20
L = random.randint(1, 10)
V = random.randint(1, 15)
Sx = random.randint(1, W)
Sy = random.randint(1, H)
print(W, H, L, V, Sx, Sy)
for y in range(H):
    print(*[random.randint(0, 15) for x in range(W)])
