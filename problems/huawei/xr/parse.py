from dataclasses import dataclass
import math
import re

testcase_re = re.compile(
    r"^#(\d+): ([^\]]+?) \[(\d+) ms, (\d+) MB, (-?[\d]+(?:\.[\d]+)?) points\]$"
)


N = 51


@dataclass
class TestCase:
    number: int
    status: str
    ms: int
    mb: int
    score: float

    def ok(self) -> bool:
        return self.status == "Accepted"

    def frames(self) -> int:
        return math.ceil(self.score)

    def perfect_score(self) -> int:
        return J[self.number - 1]


def parse(s: str) -> list[TestCase]:
    lines = s.split("\n")
    out = []
    for tc in range(N):
        print(f'matching on line "{lines[tc]}"')
        mat = testcase_re.match(lines[tc])
        num, status, ms, mb, score = mat.groups()
        num = int(num)
        ms = int(ms)
        mb = int(mb)
        score = float(score)
        assert num == tc + 1
        test = TestCase(
            number=num,
            status=status,
            ms=ms,
            mb=mb,
            score=score,
        )
        if not test.ok():
            print(f"WARNING: Test case #{test.number} has status {test.status}")
        out.append(test)
    return out


J = [
    2,
    266,
    498,
    801,
    356,
    150,
    120,
    160,
    710,
    180,
    255,
    380,
    80,
    822,
    185,
    572,
    354,
    150,
    120,
    160,
    830,
    181,
    127,
    255,
    80,
    838,
    184,
    282,
    355,
    150,
    120,
    160,
    1655,
    181,
    254,
    250,
    80,
    1658,
    185,
    806,
    358,
    150,
    120,
    160,
    835,
    182,
    255,
    380,
    80,
    826,
    184,
]
