import os
from typing import List, Iterator

from tools.http import http
from tools.http.Request import Request
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class PutTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'put'

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
        file = os.path.join(self._server_root, 'data/test.txt')
        content1 = 'hello'

        if os.path.exists(file):
            os.remove(file)

        yield Test(
            Request().set_method('PUT').set_url('/test.txt').set_body(content1),
            lambda response: response.code == http.CREATED and open(file, 'r').read() == content1
        )

        content2 = 'bye'

        yield Test(
            Request().set_method('PUT').set_url('/test.txt').set_body(content2),
            lambda response: response.code == http.NO_CONTENT and open(file, 'r').read() == content2
        )

        os.remove(file)

        yield Test(
            Request().set_method('PUT').set_url('/no/access/here'),
            lambda response: response.code == http.FORBIDDEN
        )
