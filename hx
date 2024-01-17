#!/usr/bin/python3
import sys

argv = sys.argv[1:]
argc = len(argv)

if (__name__ == "__main__"):
  out = ""
  with open(argv[0], "r") as fl:
    src = fl.read()
  for i in src.split():
    i = int(i, base=16)
    out += chr(i)
  with open(argv[1], "w") as fl:
    fl.write(out)

