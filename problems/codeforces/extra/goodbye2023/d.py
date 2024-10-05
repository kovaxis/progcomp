def multiset(x: int) -> int:
    cnt = [0 for i in range(10)]
    for c in str(x):
        cnt[ord(c) - ord("0")] += 1
    return sum(cnt[i] * 100**i for i in range(10))


found: dict[int, list[int]] = {}

maxnums = 0
for i in range(1, 1000000000):
    f = found.setdefault(multiset(i * i), [])
    f.append(i * i)
    if len(f) > maxnums:
        print(f)
        maxnums = len(f)
