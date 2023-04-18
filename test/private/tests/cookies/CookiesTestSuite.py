import os
from typing import Iterator

from tools.http.Request import Request
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class CookiesTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'cookies'

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
            Request().set_method('GET').set_url('/set_cookie.py'),
            lambda response: response.body == 'SET COOKIE'
        )

        yield Test(
            Request().set_method('GET').add_header('Cookie', 'test=ok').set_url('/check_cookie.py'),
            lambda response: response.body == 'COOKIE IS SET'
        )
