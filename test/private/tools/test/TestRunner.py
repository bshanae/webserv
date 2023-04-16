import os
import shutil
import socket
import subprocess
import time

from tools.http.Response import Response
from tools.sys.ansi import print_ansi as ansi, AnsiCode as code
from tools.sys.sys import kill_rec
from tools.test import Test, TestSuite, TestGroup
from tools.test.TestResult import TestResult
from tools.sys.ansi import *


class TestRunner:
    _temp_out_file = 'var/temp_out.log'
    _temp_err_file = 'var/temp_err.log'

    def run_test_suite(self, suite: TestSuite) -> TestResult:
        result = TestResult.OK

        server_p = self.__start_server(suite)

        for group in suite.get_test_groups():
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                try:
                    s.connect((group.get_server_address(), group.get_server_port()))
                    self.__run_test_group(s, suite, group)
                except Exception as e:
                    print_ansi('Failed to run test group: ' + str(e), AnsiCode.RED)

        self.__stop_server(suite.get_name(), server_p)

        return result

    def __start_server(self, suite: TestSuite):
        webserv_exe = '../../build/webserv'
        config_file = f'{suite.get_server_root()}/config.webserv'

        p = subprocess.Popen(
            f'{webserv_exe} {config_file} 1>{TestRunner._temp_out_file} 2>{TestRunner._temp_err_file}',
            close_fds=True,
            shell=True)
        time.sleep(0.1)

        return p

    def __stop_server(self, suite_name: str, p):
        result_code = 0
        try:
            result_code = p.wait(timeout=0.1)
        except subprocess.TimeoutExpired:
            kill_rec(p.pid)

        if result_code != 0:
            log_dir = f'var/{suite_name}'
            if not os.path.exists(log_dir):
                os.makedirs(log_dir)

            out_file = f'{log_dir}/stdout.log'
            err_file = f'{log_dir}/stderr.log'

            shutil.copyfile(TestRunner._temp_out_file, out_file)
            shutil.copyfile(TestRunner._temp_err_file, err_file)

            print_ansi('Server execution error', AnsiCode.RED)
            print_ansi(f'See stdout at {out_file}', AnsiCode.RED)
            print_ansi(f'See stderr at {err_file}', AnsiCode.RED)

        os.remove(TestRunner._temp_out_file)
        os.remove(TestRunner._temp_err_file)

    def __run_test_group(self, s: socket, suite: TestSuite, group: TestGroup) -> TestResult:
        result = TestResult.OK

        for i, test in enumerate(group.get_tests()):
            test_result = self.__run_test(s, suite, group, test, i + 1)
            if test_result == TestResult.KO:
                result = TestResult.KO

        return result

    def __run_test(self, s: socket, suite: TestSuite, group: TestGroup, test: Test, i: int) -> TestResult:
        request_str = test.request.build()
        s.sendall(bytes(test.request.build(), encoding='utf-8'))

        response_str = s.recv(4096).decode('utf-8')
        response = Response(response_str)

        test_id = f'{suite.get_name()}'
        if len(group.get_name()) > 0:
            test_id += '#' + group.get_name()
        test_id += '#' + str(i)

        if test.condition(response):
            print_ansi(f'{test_id} OK', AnsiCode.GREEN)
            return TestResult.OK
        else:
            ansi('=' * 200, code.RED)
            ansi(f'{test_id} KO', code.RED)
            ansi('REQUEST', code.RED, code.BOLD)
            ansi(request_str, code.RED)
            ansi('RESPONSE', code.RED, code.BOLD)
            ansi(response_str, code.RED)
            ansi('=' * 200, code.RED)
            return TestResult.KO
