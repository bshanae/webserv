from abc import abstractmethod
from collections.abc import Iterator
from tools.test.Test import Test


class TestGroup:
    @abstractmethod
    def get_name(self) -> str:
        pass

    @abstractmethod
    def get_server_address(self) -> str:
        pass

    @abstractmethod
    def get_server_port(self) -> int:
        pass

    @abstractmethod
    def get_tests(self) -> Iterator[Test]:
        pass
