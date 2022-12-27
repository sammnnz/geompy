# noinspection SpellCheckingInspection
"""
Tests for geompy.py
"""
import geompy.geompy as gm
import matplotlib.pyplot as plt
# noinspection PyPackageRequirements
import pytest


@pytest.fixture(scope='session')
def render_object():
    # noinspection SpellCheckingInspection
    """
    Fixture, which create instance of geompy.Render class
    """
    r = gm.Render()
    yield r
    del r


@pytest.mark.parametrize("x, y",
                         [
                             (1, 2),
                             (-2.1, 0.5)
                         ]
                         )
def test_Render_display(render_object, x, y):
    render_object.display(x, y, False)
    assert True is True


@pytest.mark.parametrize("p, c, s",
                         [
                             (gm.point(0, 0), 'orange', 50.3)
                         ]
                         )
def test_Render_points(render_object, p, c, s):
    render_object.points(p, c, s)
    assert True is True
