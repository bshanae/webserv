class AnsiCode:
    RED = '\033[91m'
    GREEN = '\033[92m'
    RESET = '\u001b[0m'
    BOLD = '\u001b[1m'


def print_ansi(s: str, *codes, end='\n'):
    if codes:
        for code in codes:
            print(code, end='')

    print(s, end=end)

    if codes:
        print(AnsiCode.RESET, end='')