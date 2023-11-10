import random
import math

N = int(2000)
M = int(1e4)

N = N // 4
print(4 * N)
for i in range(N):
    print(i, 0)
for i in range(N):
    print(N + 1, i)
for i in range(N):
    print(N + 1 - i, N + 1)
for i in range(N):
    print(0, N + 1 - i)
