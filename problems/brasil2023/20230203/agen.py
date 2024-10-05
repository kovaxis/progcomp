
import random

n = int(1e3)
m = int(1e3)
k = int(10)

print(n)
print(" ".join(str(random.randint(1, m)) for i in range(n)))
print(" ".join(str(random.randint(1, k)) for i in range(n)))
