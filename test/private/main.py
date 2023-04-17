from tools.test.TestRunner import TestRunner
from tests.get.GetTestSuite import GetTestSuite
from tests.locations.LocationsTestSuite import LocationsTestSuite
from tests.servers.ServersTestSuite import ServersTestSuite
from tests.cgi.CgiTestSuite import CgiTestSuite
from tests.upload.UploadTestSuite import UploadTestSuite
from tests.maxClientBodySize.MaxClientBodySizeTestSuite import MaxClientBodySizeTestSuite
from tests.chunkedEncoding.ChunkedEncodingTestSuite import ChunkedEncodingTestSuite

test_runner = TestRunner()

test_runner.run_test_suite(GetTestSuite())
test_runner.run_test_suite(LocationsTestSuite())
test_runner.run_test_suite(ServersTestSuite())
test_runner.run_test_suite(CgiTestSuite())
test_runner.run_test_suite(UploadTestSuite())
test_runner.run_test_suite(MaxClientBodySizeTestSuite())
test_runner.run_test_suite(ChunkedEncodingTestSuite())
