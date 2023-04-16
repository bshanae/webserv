import psutil as psutil


def kill_rec(pid):
    process = psutil.Process(pid)
    for proc in process.children(recursive=True):
        proc.kill()
    process.kill()
