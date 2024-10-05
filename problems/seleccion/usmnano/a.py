N = int(input())
for i in range(N):
    s = input().strip()
    if "/" in s:
        m, d, y = s.split("/")
    else:
        d, m, y = s.split(".")
    d = int(d)
    m = int(m)
    y = int(y)
    print("%02d.%02d.%04d %02d/%02d/%04d" % (d, m, y, m, d, y))
