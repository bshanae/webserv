#! /usr/bin/python3

import sys

print('Content-type: text/html\r\n\r\n', end='')
print(sys.stdin.read(), end='')
