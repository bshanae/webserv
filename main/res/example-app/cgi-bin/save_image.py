#!/usr/bin/python3

import cgi
import os

form = cgi.FieldStorage()

file = form['file']

print('Content-type: text/html\r\n\r\n')

if file.filename:
    if not os.path.exists('var/'):
        os.makedirs('var/')

    out_path = f'var/{os.path.basename(file.filename)}'
    if os.path.exists(out_path):
        os.remove(out_path)

    open(out_path, 'wb+').write(file.file.read())
    print('<!doctype html>', end='')
    print('<body>', end='')
    print(f'<img src="/{out_path}" alt="Image will be here" width="640" height="640">', end='')
    print('/<body>', end='')
else:
    print('ERROR', end='')
