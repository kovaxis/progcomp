#!/usr/bin/env python3

import sys


digitmap = {
    "zero": 0,
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven": 7,
    "eight": 8,
    "nine": 9,
}
opset = {"add", "sub", "mul", "rem", "pow"}


def word_err():
    print("expression evaluation stopped invalid words present")
    sys.exit()


def expr_err():
    print("expression is not complete or invalid")
    sys.exit()


def parse_digit(digit):
    if digit not in digitmap:
        word_err()
    return digitmap[digit]


def parse_token(token):
    if token in opset:
        return token
    else:
        num = 0
        for digit in map(parse_digit, token.split("c")):
            num = 10 * num + digit
        return num


tokens = list(map(parse_token, input().split()))


i = 0


def parse_expr():
    global i
    if i >= len(tokens):
        expr_err()
    token = tokens[i]
    i += 1
    if isinstance(token, str):
        # operator
        a = parse_expr()
        b = parse_expr()
        if token == "add":
            return a + b
        if token == "sub":
            return a - b
        if token == "mul":
            return a * b
        if token == "rem":
            return a % b
        if token == "pow":
            return a**b
        raise ValueError()
    else:
        # number
        return token


i = 0
result = parse_expr()
if i < len(tokens):
    expr_err()

print(result)
