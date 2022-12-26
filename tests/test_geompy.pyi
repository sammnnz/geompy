from geompy.geompy import Render, point
# noinspection PyProtectedMember
from geompy._typing import RealNumber
from typing import Sequence, Union

def test_Render_display(render_object: Render, x: RealNumber, y: RealNumber) -> None: ...
def test_Render_points(render_object: Render,
                       p: Union[point, Sequence[point]],
                       c: str,
                       s: Union[RealNumber, Sequence[RealNumber]]) -> None: ...