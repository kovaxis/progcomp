N, M = map(int, input().split())

rhyme = {}
for i in range(N):
    for word in input().split():
        word = word.lower()
        rhyme[word] = i

input()

words = []
for j in range(M):
    last = input().split()[-1].lower()
    words.append(last)

rhyme_ids = []
for j in range(M):
    last = words[j]
    if last in rhyme:
        rhyme_id = rhyme[last]
    else:
        rhyme_id = N
        N += 1

    rhyme_ids.append(rhyme_id)

count = {}
for j in range(M):
    last = words[j]
    count[rhyme_ids[j]] = count.get(rhyme_ids[j], 0) + 1

ans = []
nxt = 0
letter_for = {}
for j in range(M):
    rhyme_id = rhyme_ids[j]
    if count[rhyme_id] > 1:
        if rhyme_id in letter_for:
            ans.append(letter_for[rhyme_id])
        else:
            ans.append(nxt)
            letter_for[rhyme_id] = nxt
            nxt += 1
    else:
        ans.append(-1)

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWYZ"
ans_str = ""
for j in range(M):
    if ans[j] == -1:
        ans_str += "X"
    else:
        ans_str += alphabet[ans[j]]

print(ans_str)
