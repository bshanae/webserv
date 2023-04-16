from typing import Callable
from tools.http import Request, Response


class Test:
    def __init__(self, request: Request, condition: Callable[[Response], bool]):
        self.request = request
        self.condition = condition
