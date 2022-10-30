m = 998244353
k = 23
c = 119
for r in range(2, m):
    a = r**c % m
    for i in range(k):
        a = a * a % m
    if a == 1:
        print(f"root of unity found: {r**c % m}")
    elif r % 1024 == 0:
        print(f"at r = {r}")
else:
    print(f"no root found")
