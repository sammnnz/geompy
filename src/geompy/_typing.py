"""
_typing.py
"""
from __future__ import annotations
from typing import Tuple, Union

__all__ = ["RealNumber", "Point2D"]

RealNumber = Union[int, float]

Point2D = Tuple["RealNumber", "RealNumber"]
