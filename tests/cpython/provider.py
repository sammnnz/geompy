import os, pytest, sys

from typing import Optional

_commands = [
    "--verbose",
    "-x",
    os.path.join("tests", "cpython", "test__geompy.py"),
]

def provider(commands: Optional[list[str]] = None) -> None:
    if commands is None:
        commands = _commands
    
    try:
        pytest.main(commands, plugins=[])
    finally:
        try:
            # https://django.fun/docs/pytest/7.2/how-to/failures/
            if hasattr(sys, "last_value"):
                raise sys.last_value
                # raise exception.with_traceback(exception.__traceback__)
        except AssertionError as e:
            raise e

# Test provider
if __name__ == "__main__":
    try:
        provider()
    except Exception as e:
        assert e is AssertionError
