from tools.http.http import CRLF


class Response:
    def __init__(self, s: str):
        self.code = 0
        self.headers = {}
        self.body = ''

        header, body = s.split(CRLF * 2, 1)

        self.parse_header(header)
        self.parse_body(body)

    def parse_header(self, header: str):
        header_lines = header.splitlines()

        status_line_words = header_lines[0].split(' ')
        self.code = int(status_line_words[1])

        for header in header_lines[1:]:
            name, value = header.split(': ', 1)
            self.headers[name] = value

    def parse_body(self, body: str):
        self.body = body
