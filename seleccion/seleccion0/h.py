
import random


def iteration(start_x, start_y):
    cache = {}
    global soln
    soln = 0

    def print_board(n, board):
        print(" "+str(n)+"     ", end="")
        for b_x in range(8):
            idx = 0
            b = board
            for i in range(8):
                if b & 0x1 == 1:
                    idx = i
                    break
                b >>= 1
            board >>= 8

            print(" "+(idx+1), end="")
        print()

    def try_pos(cache, board, x):
        global soln

        if x == start_x:
            return try_pos(cache, board, x + 1)

        if board in cache:
            return
        else:
            cache[board] = True

        if x >= 8:
            # Doable board
            soln += 1
            print_board(soln, board)
            return

        forbidden = 0
        for i in range(8):
            col = (board >> (i*8)) & 0xff
            forbidden |= col
            if x > i:
                forbidden |= col >> (x - i)
                forbidden |= col << (x - i)
            elif x < i:
                forbidden |= col >> (i - x)
                forbidden |= col << (i - x)
        forbidden &= 0xff

        for i in range(8):
            if forbidden & 0x1 == 0:
                # Doable play
                try_pos(cache, board | (1 << (x*8 + i)), x+1)
            forbidden >>= 1

    print("SOLN       COLUMN")
    print(" #      1 2 3 4 5 6 7 8")
    try_pos(cache, 1 << (start_x*8+start_y), 0)


n = int(input())
input()
for i in range(n):
    [y, x] = input().split(' ')
    x = int(x) - 1
    y = int(y) - 1
    iteration(x, y)
