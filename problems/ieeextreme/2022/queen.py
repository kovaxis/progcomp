
K = 1

b = set()
x = 0
y = 0
lx = 0
ly = 0
while True:
    if y not in b:
        print(f"found diff({x-lx}, {y-ly}) : ({x}, {y})", end="")
        lx = x
        ly = y
        wait = input()
        b.add(x)
        b.add(y)
        x += K + 1
    x += 1
    y += 1
