#!/usr/bin/python3

import cgi
import os

form = cgi.FieldStorage()

file = form['file']

if file.filename:
    fn = os.path.basename(file.filename)

    if not os.path.exists('var/'):
        os.makedirs('var/')

    open('var/' + fn, 'wb+').write(file.file.read())
    print('OK', end='')
else:
    print('ERROR', end='')
