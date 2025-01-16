# noinspection SpellCheckingInspection
"""
Tests for geompy.py
"""
import ctypes
# noinspection PyPackageRequirements
import pytest

from geompy import generate_random_polygon, polygon, random_points, Render


# # # # # # # # # #
#                 #
# Tests for C API #
#                 #
# # # # # # # # # #
@pytest.mark.parametrize("points", [
    ((0, 0), (1, 2), (2, 0)),
    ((0, 0), (1, 2), (2, 0), (3, 4))
]
                         )
def test_polygon___init___valid(points):
    if len(points) != len(polygon(*points).verts):
        assert False

    for p in points:
        if p not in polygon(*points).verts:
            assert False

    assert True


@pytest.mark.parametrize("points", [
    (),
    ((0, 0),),
    ((0, 0), (1, 1)),
    ((0, 0), 1),
    (0, 1, 2),
    ("Hello", None, []),
    ((0, 0), (1, 2), (2, 0), 3),
]
                         )
def test_polygon___init___TypeError(points):
    with pytest.raises(TypeError):
        polygon(*points)


def test_polygon___new__():
    assert type(polygon.__new__(polygon)) is polygon


# https://habr.com/ru/companies/otus/articles/753554/
def count_references(address):
    """
    Count the number of references to the object at the given address.
    """
    return ctypes.c_long.from_address(address).value


# WARNING: test may be failed in debug mode
def test_polygon___del__():
    points = ((0, 0), (1, 2), (2, 0))
    ref_count = count_references(id(points[0]))
    pol = polygon(*points)
    if ref_count >= count_references(id(pol.verts[0])):
        assert False

    del pol
    if ref_count != count_references(id(points[0])):
        assert False

    assert True


def test_polygon___getitem__():
    pol = polygon((0, 0), (1, 2), (2, 0))
    for i in range(len(pol.verts)):
        if pol.verts[i] != pol[i]:
            assert False

    assert True


# TODO - write more tests for polygon.is_inner_point
def test_polygon_is_inner_point_true_return():
    point = (1, 1)
    pol = polygon((0, 0), (1, 2), (2, 0))
    assert pol.is_inner_point(point)


def test_polygon_is_inner_point_false_return():
    point = (0, 1)
    pol = polygon((0, 0), (1, 2), (2, 0))
    assert not pol.is_inner_point(point)


def test__geompy_generate_random_polygon():
    center, radius, count = (0, 2), 3, 20
    pol = generate_random_polygon(center, radius, count)
    if len(pol.verts) != count:
        assert False

    for v in pol.verts:
        if (v[0] - center[0])**2 + (v[1] - center[1])**2 > radius**2:
            assert False

    assert True


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
