
# polynomials are represented as arrays of coefficients, where p[0] is the constant coefficient
# and p[-1] is the coefficient for the highest power of x

# return the product of two polynomials.
def mult(lhs, rhs):
    poly = [0 for k in range(len(lhs) + len(rhs) - 1)]
    for i in range(len(lhs)):
        for j in range(len(rhs)):
            poly[i+j] += lhs[i] * rhs[j]
    return poly


# return the sum of two polynomials.
def add(lhs, rhs):
    poly = [0 for k in range(max(len(lhs), len(rhs)))]
    for i in range(len(lhs)):
        poly[i] += lhs[i]
    for j in range(len(rhs)):
        poly[j] += rhs[j]
    return poly


# parse an equation into a polynomial.
class Reader:
    # parse the string `s`.
    def __init__(self, s):
        self.s = s
        # next character
        self.i = 0
        # highest digit found
        self.hid = 1

    # next character.
    def peek(self):
        return self.s[self.i]

    # consume next character.
    def pop(self):
        c = self.peek()
        self.i += 1
        return c

    # are there no more characters left?
    def eof(self):
        return self.i >= len(self.s)

    # read a single number as a polynomial.
    def read_num(self):
        poly = []
        while not self.eof() and self.peek() >= '0' and self.peek() <= '9':
            digit = ord(self.pop()) - ord('0')
            self.hid = max(self.hid, digit)
            poly.insert(0, digit)
        return poly

    # read a single group of numbers grouped by `*`.
    def read_mul(self):
        poly = [1]
        while True:
            sub = self.read_num()
            poly = mult(poly, sub)
            if self.eof() or self.peek() != '*':
                break
            self.pop()
        return poly

    # read a single group of numbers grouped by `+` and `*`.
    def read_add(self):
        poly = []
        while True:
            sub = self.read_mul()
            poly = add(poly, sub)
            if self.eof() or self.peek() != '+':
                break
            self.pop()
        return poly

    # read an equation and return a polynomial such that the roots of this polynomial solve the
    # equation, and only the roots do.
    def read_eq(self):
        l = self.read_add()
        self.pop()
        r = self.read_add()
        for i in range(len(r)):
            r[i] = -r[i]
        return add(l, r)


# factorize a positive integer `x` into its prime factors.
# returns an array of tuples, where each tuple represents a prime factor, and is of the form
# `(k, n)`, where `k` is a prime number and `n` represents the multiplicity of this prime.
def factorize(x):
    facts = []
    k = 2
    while x > 1:
        if k * k > x:
            facts.append((x, 1))
            break
        n = 0
        while x % k == 0:
            x = x // k
            n += 1
        if n > 0:
            facts.append((k, n))
        k += 1
    return facts


# solve a test case for the given polynomial and highest digit in the equation.
def solve(poly, hidig):
    # remove leading and trailing zeros in the polynomial
    while poly and poly[-1] == 0:
        poly.pop()
    while poly and poly[0] == 0:
        poly.pop(0)

    # if the polynomial is constant 0, any base over the highest digit works
    if not poly:
        print(str(hidig+1)+"+")
        return

    # get the factors of the constant term
    facts = factorize(abs(poly[0]))

    # iterate over all divisors of the constant term
    f = [0 for f in facts]
    ans = []
    while True:
        # calculate this divisor by multiplying its prime components
        x = 1
        for i in range(len(f)):
            for j in range(f[i]):
                x *= facts[i][0]

        # evaluate the polynomial
        xpow = 1
        y = 0
        for k in poly:
            y += k * xpow
            xpow *= x

        # add this solution if the polynomial evaluates to zero AND the base is over the highest
        # digit in the equation
        if y == 0 and x > hidig:
            ans.append(x)

        # advance to the next divisor
        for i in range(len(f)):
            f[i] += 1
            if f[i] > facts[i][1]:
                f[i] = 0
            else:
                break
        else:
            break

    # print the answers
    if ans:
        ans.sort()
        for i in range(len(ans)):
            ans[i] = str(ans[i])
        print(" ".join(ans))
    else:
        print("*")


while True:
    # a single testcase
    line = input().strip()
    if line == "=":
        break
    r = Reader(line)
    poly = r.read_eq()
    solve(poly, r.hid)
