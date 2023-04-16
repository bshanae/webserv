import os
from typing import Iterator

from tools.http import http
from tools.http.Request import Request
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class LocationsTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'locations'

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
        # basic

        yield Test(
            Request().set_method('GET').set_url('/pages-1/page-a.html'),
            lambda response: response.body == 'PAGE A'
        )

        yield Test(
            Request().set_method('GET').set_url('/pages-2/page-b.html'),
            lambda response: response.body == 'PAGE B'
        )

        yield Test(
            Request().set_method('GET').set_url('/pages-2/page-c.html'),
            lambda response: response.body == 'PAGE C'
        )

        # basic : errors

        yield Test(
            Request().set_method('GET').set_url('/pages-2/page-a.html'),
            lambda response: response.code == http.NOT_FOUND
        )

        yield Test(
            Request().set_method('GET').set_url('/pages-1/page-b.html'),
            lambda response: response.code == http.NOT_FOUND
        )

        yield Test(
            Request().set_method('GET').set_url('/pages-1/page-c.html'),
            lambda response: response.code == http.NOT_FOUND
        )

        # aliases

        yield Test(
            Request().set_method('GET').set_url('/page-a.html'),
            lambda response: response.body == 'PAGE A'
        )

        yield Test(
            Request().set_method('GET').set_url('/alias/page-b.html'),
            lambda response: response.body == 'PAGE B'
        )

        yield Test(
            Request().set_method('GET').set_url('/alias/page-c.html'),
            lambda response: response.body == 'PAGE C'
        )

        yield Test(
            Request().set_method('GET').set_url('/redirect'),
            lambda response: response.code == http.REDIRECT and
                             response.headers['Location'] == '/pages-2/page-c.html'
        )
