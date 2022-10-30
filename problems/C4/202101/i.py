
class Segment:
    def __init__(self, color, length):
        self.color = color
        self.length = length

    def clone(self):
        return Segment(self.color, self.length)

    def print(segs):
        print("segments:")
        for seg in segs:
            print(f"  color: {seg.color}, len: {seg.length}")


segments = []

raw = input()
letter = None
length = 0
for c in raw:
    if c == letter:
        length += 1
    else:
        if letter != None:
            segments.append(Segment(letter, length))
        letter = c
        length = 1

if letter != None:
    segments.append(Segment(letter, length))


def check_empties(segments):
    while True:
        deleted = False
        idx = 1
        while idx < len(segments):
            if idx < 1:
                idx = 1
                continue
            if segments[idx - 1].color == segments[idx].color:
                # Merge segments
                segments[idx].length += segments[idx - 1].length
                if segments[idx].length >= 3:
                    del segments[idx]
                    idx -= 1
                del segments[idx - 1]
                deleted = True
            else:
                idx += 1

        if not deleted:
            break
    return len(segments) == 0


ways = 0
for i in range(len(segments)):
    if segments[i].length >= 2:
        new_segs = []
        for j in range(len(segments)):
            if j != i:
                new_segs.append(segments[j].clone())
        if check_empties(new_segs):
            ways += segments[i].length + 1

print(ways)
