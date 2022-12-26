"""
Example
"""
from geompy.geompy import generate_random_polygon, point, random_points, Render

if __name__ == '__main__':
    center, radius = point(0, 2), 3
    rand_points = random_points(20, radius, center[0], center[1])
    rand_polygon = generate_random_polygon(center, radius, 8)
    render = Render()
    for p in rand_points:
        render.points(p=p, c='black', s=500)
        if rand_polygon.is_inner_point(p):
            render.points(p=p, c='red', s=500)
        else:
            render.points(p=p, c='blue', s=500)

    render.polygon(p=rand_polygon, c='green')
    render.display()
