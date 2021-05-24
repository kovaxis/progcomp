
n, c, s = input().split(' ')
n = int(n)
c = int(c)
s = int(s) - 1

cmds = input().split(' ')

pos = 0
times = 0
if s == 0:
    times += 1
for cmd in cmds:
    if cmd == "1":
        pos += 1
    else:
        pos -= 1
    pos = pos % n
    if pos == s:
        times += 1

print(times)
