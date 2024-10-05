#!/usr/bin/env python3

import json
import sys

lines = sys.stdin.read().replace("\r", "").split("\n")
lines = [line for line in lines if line]

values = list(map(int, lines.pop().split()))
vars = lines.pop().split()

vars = {var.lower(): val for var, val in zip(vars, values)}

src = "["
for line in lines:
    if line[:2].lower() == "is":
        cond = line[2:].lower()
        for var, val in vars.items():
            cond = cond.replace(var.lower(), str(val))
        cond = eval(cond)
        src += '{"cond":' + str(cond).lower()
    elif line[:2].lower() == "si":
        if src[-1:] == ",":
            src = src[:-1]
        src += "]},"
    elif line[:3].lower() == "yes":
        src += ',"true":['
    elif line[:2].lower() == "no":
        if src[-1:] == ",":
            src = src[:-1]
        src += '],"false":['
    elif line[:5].lower() == "print":
        src += '"' + line[6] + '",'
if src[-1:] == ",":
    src = src[:-1]
src += "]"


def evaluate(prog):
    for line in prog:
        if isinstance(line, str):
            print(vars[line.lower()])
        else:
            condval = str(line["cond"]).lower()
            if condval in line:
                evaluate(line[condval])


# print("src = " + src)
prog = None
try:
    prog = json.loads(src)
except Exception:
    pass
if prog is not None:
    evaluate(prog)
