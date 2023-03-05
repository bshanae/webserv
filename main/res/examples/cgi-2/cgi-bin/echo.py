#! /usr/bin/python3

import sys

print("Content-type:text/html\r\n\r\n")
print('<html>')
print('<head>')
print('<title>Hello Word - First CGI Program</title>')
print('</head>')
print('<body>')
print(sys.stdin.read())
print('</body>')
print('</html>')
