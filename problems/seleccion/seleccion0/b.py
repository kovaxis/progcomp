
def test():

    n = int(input())

    papers = input().split(' ')
    for i in range(n):
        papers[i] = int(papers[i])
    papers.sort(reverse=False)

    h = 0
    for i in range(n):
        if n - i <= h:
            break
        this_h = min(n - i, papers[i])
        if this_h > h:
            h = this_h

    print(h)


tests = int(input())
for i in range(tests):
    test()
