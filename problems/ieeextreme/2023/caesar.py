import sys

n = int(input())
for i in range(n):
    k = int(input())
    s = input().strip()
    if " the " in s or s.startswith("the ") or s.endswith(" the") or s == "the":
        k = -k
    else:
        k = k
    ss = ""
    print(f"using k = {k}", file=sys.stderr)
    for c in s:
        j = ord(c) - ord("a")
        if j >= 0 and j < 26:
            j += k
            j %= 26
        j += ord("a")
        ss += chr(j)
    print(ss)
