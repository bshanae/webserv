#!/usr/bin/python3

import cgi
import os

form = cgi.FieldStorage()

fileitem = form['file']
if fileitem.filename:
    fn = os.path.basename(fileitem.filename)
    open('temp/' + fn, 'wb+').write(fileitem.file.read())
    message = 'The file "' + fn + '" was uploaded successfully'

else:
    message = 'No file was uploaded'

print("Content-type:text/html\r\n\r\n")
print("<html>")
print("<body>")
print(message)
print("</body>")
print("</html>")

