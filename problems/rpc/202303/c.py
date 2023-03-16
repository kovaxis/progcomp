n, k = map(int, input().split())
d, s = map(int, input().split())
ans = (n*d - k*s) / (n-k)
if 0 <= ans <= 100:
    print(f"{ans}")
else:
    print("impossible")
