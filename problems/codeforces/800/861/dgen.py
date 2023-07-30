from random import randint

N = int(2e5)
print(N, int(N**0.5))
for i in range(N):
    print(randint(1, int(2e5)))
