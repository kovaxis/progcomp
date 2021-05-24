
def is_rect():
    def seg():
        [x0, y0, x1, y1] = input().split(' ')
        return int(x0), int(y0), int(x1), int(y1)

    def parallel(x0, x1, y0, y1, x2, x3, y2, y3):
        return y0 == y1 and y2 == y3 and y0 != y2 and ((x2 == x0 and x3 == x1) or (x3 == x0 and x2 == x1))

    def shared(sx0, sy0, x1, y1, x2, y2):
        return sx0, y1, x2, y1,   x2, sy0, x2, y1

    x0, y0, x1, y1 = seg()
    x2, y2, x3, y3 = seg()
    x4, y4, x5, y5 = seg()
    x6, y6, x7, y7 = seg()

    def find_corner(x0, y0, x1, y1, x2, y2, x3, y3):
        if x0 == x2 and y0 == y2:
            return x0, y0
        elif x0 == x3 and y0 == y3:
            return x0, y0
        elif x1 == x2 and y1 == y2:
            return x1, y1
        elif x1 == x3 and y1 == y3:
            return x1, y1
        else:
            return None, None

    def flip_seg(cx, cy, x0, y0, x1, y1):
        if cx == x0 and cy == y0:
            return x0, y0, x1, y1
        elif cx == x1 and cy == y1:
            return x1, y1, x0, y0

    cx0, cy0 = find_corner(x0, y0, x1, y1, x2, y2, x3, y3)
    if cx0 == None:
        # Segments are parallel
        cx0, cy0 = find_corner(x0, y0, x1, y1, x4, y4, x5, y5)
        if cx0 == None:
            cx0, cy0 = find_corner(x0, y0, x1, y1, x6, y6, x7, y7)
            if cx0 == None:
                return False
            else:
                x2, y2, x3, y3, x6, y6, x7, y7 = x6, y6, x7, y7, x2, y2, x3, y3
        else:
            x2, y2, x3, y3, x4, y4, x5, y5 = x4, y4, x5, y5, x2, y2, x3, y3

    cx1, cy1 = find_corner(x4, y4, x5, y5, x6, y6, x7, y7)
    if cx1 == None:
        return False

    if cx0 == cx1 or cy0 == cy1:
        return False

    x0, y0, x1, y1 = flip_seg(cx0, cy0, x0, y0, x1, y1)
    x2, y2, x3, y3 = flip_seg(cx0, cy0, x2, y2, x3, y3)
    x4, y4, x5, y5 = flip_seg(cx1, cy1, x4, y4, x5, y5)
    x6, y6, x7, y7 = flip_seg(cx1, cy1, x6, y6, x7, y7)

    if x1 == x0:
        pass
    elif y1 == y0:
        x0, y0, x1, y1, x2, y2, x3, y3 = x2, y2, x3, y3, x0, y0, x1, y1
    else:
        return False
    if x0 != x1 or y2 != y3:
        return False

    if x5 == x4:
        pass
    elif y5 == y4:
        x4, y4, x5, y5, x6, y6, x7, y7 = x6, y6, x7, y7, x4, y4, x5, y5
    else:
        return False
    if x4 != x5 or y6 != y7:
        return False

    if y1 == cy1 and x3 == cx1 and y5 == cy0 and x7 == cx0:
        return True
    else:
        return False


if is_rect():
    print("YES")
else:
    print("NO")
