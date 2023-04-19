import os
from typing import List, Iterator

from tools.http import http
from tools.http.Request import Request
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class GetTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'get'

    def get_server_root(self) -> str:
        return os.path.join(os.path.dirname(__file__), 'res')

    def get_test_groups(self) -> Iterator[type[TestGroup]]:
        yield MainTestGroup()


class MainTestGroup(TestGroup):
    def get_name(self) -> str:
        return ''

    def get_server_address(self) -> str:
        return '0.0.0.0'

    def get_server_port(self) -> int:
        return 8080

    def get_tests(self) -> Iterator[Test]:
        yield Test(
            Request().set_method('GET').set_url('/'),
            lambda response: 'hello.txt' in response.body
        )

        yield Test(
            Request().set_method('GET').set_url('/hello.txt'),
            lambda response: response.code == http.OK and response.body == 'Hello'
        )

        yield Test(
            Request().set_method('GET').set_url('/bye.txt'),
            lambda response: response.code == http.NOT_FOUND
        )

        yield Test(
            Request().set_method('POST').set_url('/'),
            lambda response: response.code == http.NOT_ALLOWED
        )

        yield Test(
            Request().set_method('POST').set_url('/hello.txt'),
            lambda response: response.code == http.NOT_ALLOWED
        )