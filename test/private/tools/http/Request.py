from typing import List

from tools.http.http import CRLF


class Request:
    SPLIT = '@@SPLIT@@'

    def __init__(self):
        self._method = ''
        self._url = ''
        self._headers = []
        self._body = ''

    def set_method(self, method: str):
        self._method = method
        return self

    def set_url(self, url: str):
        self._url = url
        return self

    def add_header(self, name: str, value: str):
        self._headers.append(f'{name}: {value}')
        return self

    def set_body(self, body: str):
        self._body = body
        self.add_header('Content-Length', str(len(body)))
        return self

    def build(self) -> List[str]:
        result = ''

        result += f'{self._method} {self._url} HTTP/1.1' + CRLF

        for header in self._headers:
            result += header + CRLF
        result += CRLF

        result += self._body

        return result.split(Request.SPLIT)
