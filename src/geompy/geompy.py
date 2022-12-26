"""
GeomPy - Python/C library for geometry calculations
"""
import math
import matplotlib.pyplot as plt
import numpy as np
import random

from _geompy import *  # noqa: F401, F403


# TODO: implement in C
class point(tuple):
    """
    Point object class.

    """
    def __new__(cls, *args):
        # noinspection PyArgumentList
        return super(__class__, cls).__new__(cls, args)


# noinspection PyTypeChecker
class Render(object):
    """
    Class for rendering geometry objects (based on matplotlib).

    You can use the Render class for example like this:

    >>> r = Render()
    >>> p1, p2, p3 =  point(0, 0), point(1, 2), point(2, 1)
    >>> r.points((p1, p2), c='black')
    >>> r.polygon(polygon(p1, p2, p3))
    >>> r.display(0, 0) # Created plots are displayed
    """
    ax = None
    fig = None

    def __init__(self):
        self.ax = plt
        self.fig = self.ax.figure(figsize=(25, 25), dpi=50)

    def display(self, x=None, y=None):
        """
        Draws a plots.

        :param x: integer or float, optional
                  X limit of current axes.
        :param y: integer or float, optional
                  Y limit of current axes.
        """
        plt.xlim(x)
        plt.ylim(y)
        self.ax.show()

    def points(self, p, c='red', s=40):
        """
        Creates a points plot.

        :param p: array-like or point object
                  Points to create a plot.
        :param c: string with color, default: 'red'
                  The color that the points will be drawn with.
        :param s: integer, float or array-like, default: 40
                  Size of points.
        """
        try:
            p[0][0]
        except TypeError:
            p = [p]

        arr = np.array(p)
        self.ax.scatter(arr[:, 0], arr[:, 1], color=c, s=s)

    def polygon(self, p, c='green'):
        """
        Creates a polygon plot.

        :param p: polygon object
                  Polygon to create a plot.
        :param c: string with color, default: 'green'
                  The color that the points will be drawn with.
        """
        # noinspection SpellCheckingInspection
        verts = p.verts
        for i in range(len(verts)):
            x, y = [verts[i - 1][0], verts[i][0]], [verts[i - 1][1], verts[i][1]]
            self.ax.plot(x, y, c=c, linewidth=1.55)


# noinspection PyTypeChecker
def random_points(count, radius, x, y):
    """
    Generate random points.

    :param count: integer
                  Count of points.
    :param radius: integer or float
                   Radius of random.
    :param x: integer or float
              X coord of center
    :param y: integer or float
              Y coord of center
    :return: Generator of point
    """
    for i in range(0, count):
        yield point(random.uniform(0, radius) * math.sin(i) + x, random.uniform(0, radius) * math.cos(i) + y)
