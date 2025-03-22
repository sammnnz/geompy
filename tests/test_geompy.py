# noinspection SpellCheckingInspection
"""
Python API tests for geompy
"""
# noinspection PyPackageRequirements
import pytest

from geompy import polygon, random_points, Render


# # # # # # # # # # # # #
#                       #
# Tests for Python API  #
#                       #
# # # # # # # # # # # # #
@pytest.fixture(scope='session')
def render_object():
    # noinspection SpellCheckingInspection
    """
    Fixture, which create instance of geompy.Render class.
    """
    r = Render()
    yield r
    del r


@pytest.mark.parametrize("x, y", [
    (-2.1, 0.5)
]
                         )
def test_Render_display(render_object, x, y):
    assert render_object.display(x, y) is None


@pytest.mark.parametrize("args, c, s", [
    (((0, 0), (1, 1)), 'orange', 50.3)
]
                         )
def test_Render_points(render_object, args, c, s):
    assert render_object.points(*args, c=c, s=s) is None


def test_Render_polygon(render_object):
    assert render_object.polygon(polygon((0, 0), (1, 2), (0, 2))) is None


def test_random_points():
    center, radius, count = (0, 2), 3, 20
    points = random_points(count, radius, center[0], center[1])
    for p in points:
        if (p[0] - center[0]) ** 2 + (p[1] - center[1]) ** 2 > radius ** 2:
            assert False

    assert True
