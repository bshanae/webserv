import os
from typing import Iterator

from tools.http.Request import Request
from tools.http.http import CRLF
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class ChunkedEncodingTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'chunks'

    def get_server_root(self) -> str:
        return os.path.join(os.path.dirname(__file__), 'res')

    def get_test_groups(self) -> Iterator[type[TestGroup]]:
        yield MainTestGroup(self.get_server_root())


class MainTestGroup(TestGroup):
    def __init__(self, server_root: str):
        self._server_root = server_root

    def get_name(self) -> str:
        return ''

    def get_server_address(self) -> str:
        return '0.0.0.0'

    def get_server_port(self) -> int:
        return 8080

    def get_tests(self) -> Iterator[Test]:
        body1 = f'9{CRLF}chunk 1, {CRLF}' \
                f'7{CRLF}chunk 2{CRLF}' \
                f'0{CRLF}{CRLF}'

        yield Test(
            Request()
            .set_method('GET')
            .set_url('/echo.py')
            .add_header('Transfer-Encoding', 'chunked')
            .set_body(body1),
            lambda response: response.body == 'chunk 1, chunk 2'
        )

        body2 = f'a{CRLF}chu{Request.SPLIT}nk 12, {CRLF}' \
                f'1{CRLF}c{CRLF}' \
                f'0{CRLF}{CRLF}'

        yield Test(
            Request()
            .set_method('GET')
            .set_url('/echo.py')
            .add_header('Transfer-Encoding', 'chunked')
            .set_body(body2),
            lambda response: response.body == 'chunk 12, c'
        )

        body3 = f'9{CRLF}c{Request.SPLIT}h{Request.SPLIT}u{Request.SPLIT}nk 1{Request.SPLIT}23{CRLF}' \
                f'0{CRLF}{Request.SPLIT}{CRLF}'

        yield Test(
            Request()
            .set_method('GET')
            .set_url('/echo.py')
            .add_header('Transfer-Encoding', 'chunked')
            .set_body(body3),
            lambda response: response.body == 'chunk 123'
        )
