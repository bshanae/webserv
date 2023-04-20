#! /usr/bin/python3

import sys

print("Content-type:text/html\r\n\r\n")
print('<html>')
print('<body>')
print(sys.stdin.read().replace('input=', ''))
print('</body>')
print('</html>')
