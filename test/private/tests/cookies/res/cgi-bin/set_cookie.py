#!/usr/bin/env python3

import os
import http.cookies

cookie = http.cookies.SimpleCookie(os.environ.get('HTTP_COOKIE'))

print('Set-cookie: name=value\r\n', end='')
print('Content-type: text/html\r\n\r\n', end='')
print('SET COOKIE', end='')
