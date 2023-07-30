import sys

out = []
with open(sys.argv[1], 'r') as f:
    for l in f.readlines():
        out.append(int(l))

ans = []
with open(sys.argv[2], 'r') as f:
    for l in f.readlines():
        ans.append(int(l))


def luckiness(x):
    mn = 100
    mx = 0
    while x != 0:
        mn = min(mn, x % 10)
        mx = max(mx, x % 10)
        x //= 10
    assert mn <= mx
    return mx - mn


assert len(out) == len(ans)
for i in range(len(ans)):
    a = luckiness(ans[i])
    o = luckiness(out[i])
    if a != o:
        print(
            f"line {i+1}: {out[i]} has score {o} but answer {ans[i]} has score {a}")
