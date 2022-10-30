
class Link:
    def __init__(self, x0, y0, z0, x1, y1, z1):
        self.x0 = int(x0)
        self.y0 = int(y0)
        self.z0 = int(z0)
        self.x1 = int(x1)
        self.y1 = int(y1)
        self.z1 = int(z1)


def test(x0, y0, x1, y1, z, x, y, z0, z1):
    if x1 < x0:
        x0, x1 = x1, x0
    if y1 < y0:
        y0, y1 = y1, y0
    if z1 < z0:
        z0, z1 = z1, z0
    return x >= x0 and x <= x1 and y >= y0 and y <= y1 and z >= z0 and z <= z1


def test_links(a, b):
    if a.x0 == a.x1 and b.x0 != b.x1:
        if test(a.z0, a.y0, a.z1, a.y1, a.x0,   b.z0, b.y0, b.x0, b.x1) or test(a.z0, a.y0, a.z1, a.y1, a.x0,   b.z0, b.y1, b.x0, b.x1) or test(a.z0, a.y0, a.z1, a.y1, a.x0,   b.z1, b.y0, b.x0, b.x1) or test(a.z0, a.y0, a.z1, a.y1, a.x0,   b.z1, b.y1, b.x0, b.x1):
            return True
    elif a.y0 == a.y1 and b.y0 != b.y1:
        if test(a.x0, a.z0, a.x1, a.z1, a.y0,   b.x0, b.z0, b.y0, b.y1) or test(a.x0, a.z0, a.x1, a.z1, a.y0,   b.x0, b.z1, b.y0, b.y1) or test(a.x0, a.z0, a.x1, a.z1, a.y0,   b.x1, b.z0, b.y0, b.y1) or test(a.x0, a.z0, a.x1, a.z1, a.y0,   b.x1, b.z1, b.y0, b.y1):
            return True
    elif a.z0 == a.z1 and b.z0 != b.z1:
        if test(a.x0, a.y0, a.x1, a.y1, a.z0,   b.x0, b.y0, b.z0, b.z1) or test(a.x0, a.y0, a.x1, a.y1, a.z0,   b.x0, b.y1, b.z0, b.z1) or test(a.x0, a.y0, a.x1, a.y1, a.z0,   b.x1, b.y0, b.z0, b.z1) or test(a.x0, a.y0, a.x1, a.y1, a.z0,   b.x1, b.y1, b.z0, b.z1):
            return True
    return False


def do_test():
    input()
    links = []
    n = int(input())
    for i in range(n):
        x0, y0, z0, x1, y1, z1 = input().split()
        links.append(Link(x0, y0, z0, x1, y1, z1))

    connections = []
    for i in range(n):
        connections.append({})

    for i in range(n):
        for j in range(i+1, n):
            if test_links(links[i], links[j]):
                connections[i][j] = True
                connections[j][i] = True

    can_be_done = False
    for assuming_a in range(n):
        # Assume link `assuming_a` is in set A
        bset = connections[assuming_a].copy()
        aset = []
        for i in range(n):
            if i not in bset:
                aset.append(i)
        idx = 0
        while idx < len(aset):
            a = aset[idx]
            for i in bset.copy().keys():
                if i not in connections[a]:
                    del bset[i]
                    aset.append(i)
            idx += 1

        if len(bset) != 0:
            can_be_done = True
            break

    if can_be_done:
        print("YES")
    else:
        print("NO")


t = int(input())
for i in range(t):
    do_test()
