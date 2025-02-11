"""
C/API tests for _geompy
"""
import ctypes
# noinspection PyPackageRequirements
import pytest

from geompy import polygon, generate_random_polygon

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
