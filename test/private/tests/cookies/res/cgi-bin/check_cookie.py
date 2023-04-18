#!/usr/bin/env python3

import os
import http.cookies

cookie = http.cookies.SimpleCookie(os.environ.get('HTTP_COOKIE'))

print('Content-type: text/html\r\n\r\n', end='')

if cookie.get('test').value == 'ok':
    print('COOKIE IS SET', end='')
else:
    print('COOKIE IS NOT SET', end='')
