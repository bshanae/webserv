import os
from typing import Iterator

from tools.http.Request import Request
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class CgiTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'cgi'

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
            Request().set_method('GET').set_url('/cgi-1/hello.py'),
            lambda response: response.body == 'Hello'
        )

        yield Test(
            Request().set_method('POST').set_url('/cgi-1/echo.py').set_body('echo'),
            lambda response: response.body == 'echo'
        )

        yield Test(
            Request().set_method('POST').set_url('/cgi-1/submit_name.py?first_name=Leo&last_name=Tolstoy').set_body('echo'),
            lambda response: response.body == 'Hello, Leo Tolstoy'
        )

        yield Test(
            Request().set_method('GET').set_url('/cgi-2/hello.py'),
            lambda response: response.body == 'Hello from another directory'
        )
