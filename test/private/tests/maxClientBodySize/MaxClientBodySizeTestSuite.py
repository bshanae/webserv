import os
from typing import Iterator

from tools.http import http
from tools.http.Request import Request
from tools.http.http import CRLF
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class MaxClientBodySizeTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'max_client_body_size'

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
        yield Test(
            Request().set_method('GET').set_url('/').set_body('A' * 10),
            lambda response: response.code == http.OK
        )

        yield Test(
            Request().set_method('GET').set_url('/').set_body('A' * 100),
            lambda response: response.code == http.OK
        )

        yield Test(
            Request().set_method('GET').set_url('/').set_body('A' * 1000),
            lambda response: response.code == http.PAYLOAD_TOO_LARGE
        )
