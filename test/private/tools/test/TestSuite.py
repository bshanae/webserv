from abc import abstractmethod
from collections.abc import Iterator
from tools.test import TestGroup


class TestSuite:
    @abstractmethod
    def get_name(self) -> str:
        pass

    @abstractmethod
    def get_server_root(self) -> str:
        pass

    @abstractmethod
    def get_test_groups(self) -> Iterator[type[TestGroup]]:
        pass
