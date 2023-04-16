import os
from typing import List, Iterator

from tools.http.Request import Request
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class ServersTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'servers'

    def get_server_root(self) -> str:
        return os.path.join(os.path.dirname(__file__), 'res')

    def get_test_groups(self) -> Iterator[type[TestGroup]]:
        yield ServerATestGroup()
        yield ServerBTestGroup()
        yield ServerCTestGroup()


class ServerATestGroup(TestGroup):
    def get_name(self) -> str:
        return 'a'

    def get_server_address(self) -> str:
        return '0.0.0.0'

    def get_server_port(self) -> int:
        return 8080

    def get_tests(self) -> Iterator[Test]:
        yield Test(
            Request().set_method('GET').set_url('/'),
            lambda response: response.body == 'SERVER A'
        )


class ServerBTestGroup(TestGroup):
    def get_name(self) -> str:
        return 'b'

    def get_server_address(self) -> str:
        return '0.0.0.0'

    def get_server_port(self) -> int:
        return 8081

    def get_tests(self) -> Iterator[Test]:
        yield Test(
            Request().set_method('GET').set_url('/').add_header('Host', 's-b'),
            lambda response: response.body == 'SERVER B'
        )

        # check that a first suitable server responds to request
        # s-b and s-c have same port, but s-b is first in config, so it should respond
        yield Test(
            Request().set_method('GET').set_url('/'),
            lambda response: response.body == 'SERVER B'
        )


class ServerCTestGroup(TestGroup):
    def get_name(self) -> str:
        return 'c'

    def get_server_address(self) -> str:
        return '0.0.0.0'

    def get_server_port(self) -> int:
        return 8081

    def get_tests(self) -> Iterator[Test]:
        yield Test(
            Request().set_method('GET').set_url('/').add_header('Host', 's-c'),
            lambda response: response.body == 'SERVER C'
        )
