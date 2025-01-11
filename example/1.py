"""
Example
"""
from geompy import generate_random_polygon, random_points, Render

if __name__ == '__main__':
    count, center, radius = 20, (0, 2), 3
    rand_points = random_points(count, radius, center[0], center[1])
    rand_polygon = generate_random_polygon(center, radius, 8)
    render = Render()
    for p in rand_points:
        if rand_polygon.is_inner_point(p):
            render.points(p, c='red', s=500)
        else:
            render.points(p, c='blue', s=500)

    render.polygon(p=rand_polygon, c='green')
    render.points(*rand_polygon.verts, c='black', s=100)
    render.display()
