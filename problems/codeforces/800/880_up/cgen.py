import random

K = 17
print(1)
print(K)
a = [random.randint(1, 4**K - 1) for i in range(2 ** (K + 1) - 1)]
a.insert(random.randint(0, len(a)), 0)
print(*a)
