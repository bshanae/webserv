import os
from typing import Iterator

from tools.http import http
from tools.http.Request import Request
from tools.http.http import CRLF
from tools.test.TestGroup import TestGroup
from tools.test.TestSuite import TestSuite
from tools.test.Test import Test


class UploadTestSuite(TestSuite):
    def get_name(self) -> str:
        return 'upload'

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
        boundary = '----TEST_BOUNDARY'
        body = f'--{boundary}{CRLF}' \
               f'Content-Disposition: form-data; name="file"; filename="upload_test.txt"{CRLF}' \
               f'Content-Type: text/plain{CRLF}' \
               f'{CRLF}' \
               f'upload_test{CRLF}' \
               f'--{boundary}--{CRLF}'

        target_file = os.path.join(self._server_root, 'var/upload_test.txt')
        target_file_content = 'upload_test'

        yield Test(
            Request()
            .set_method('POST')
            .set_url('/save_file.py')
            .add_header('Content-Type', f'multipart/form-data; boundary={boundary}')
            .set_body(body),
            lambda response: response.code == http.OK
                             and open(target_file, 'r').read() == target_file_content
        )
