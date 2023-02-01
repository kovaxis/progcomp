
import random

m = int(1e2)

n = int(1e1)
print(n)
for i in range(n):
    print(random.randint(1, m))

q = int(1e1)
print(q)
for qi in range(q):
    l = random.randint(1, n)
    r = random.randint(l, n)
    w = random.randint(1, r - l + 1)
    print(l, r, w)
