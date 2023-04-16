#! /usr/bin/python3

import cgi

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
first_name = form.getvalue('first_name')
last_name = form.getvalue('last_name')

print('Content-type:text/html\r\n\r\n', end='')
print(f'Hello, {first_name} {last_name}', end='')
