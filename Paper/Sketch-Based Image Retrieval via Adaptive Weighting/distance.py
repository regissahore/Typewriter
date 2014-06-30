import math
from PIL import Image, ImageFilter


PENALTY_VALUE = 30.0
WINDOW_SIZE = 8
SPACE_SIMILARITY = 8.0
ORIENTATION_SIMILARITY = 0.5


def is_inside(image, x, y):
    (width, height) = image.size
    return x >= 0 and x < width and y >= 0 and y < height
    
    
def get_gray(image, x, y):
    if not is_inside(image, x, y):
        return 0.0
    return image.getpixel((x, y)) / 255.0
    
    
def get_angle(image, x, y):
    dx1 = get_gray(image, x, y) - get_gray(image, x - 1, y)
    dx2 = get_gray(image, x + 1, y) - get_gray(image, x, y)
    dx = dx2 - dx1
    dy1 = get_gray(image, x, y) - get_gray(image, x, y - 1)
    dy2 = get_gray(image, x, y + 1) - get_gray(image, x, y)
    dy = dy2 - dy1
    return math.atan2(dy, dx)

    
def distance(image1, image2):
    cost_total = 0.0
    (width, height) = image1.size
    gray1 = [[get_gray(image1, x, y) for y in range(height)] for x in range(width)]
    gray2 = [[get_gray(image2, x, y) for y in range(height)] for x in range(width)]
    angle1 = [[get_angle(image1, x, y) for y in range(height)] for x in range(width)]
    angle2 = [[get_angle(image2, x, y) for y in range(height)] for x in range(width)]
    for x in range(width):
        for y in range(height):
            if gray1[x][y] < 0.5:
                continue
            cost_pixel = 100.0
            for sx in range(-6, 7):
                for sy in range(-6, 7):
                    if sx ** 2 + sy ** 2 >= 36:
                        continue
                    tx = x + sx
                    ty = y + sy
                    tx = (tx + width) % width
                    ty = (ty + height) % height
                    if gray2[tx][ty] < 0.5:
                        continue
                    cost_temp = 0.0
                    for bx in range(-8, 9):
                        for by in range(-8, 9):
                            tx1 = x + bx
                            ty1 = y + by
                            tx1 = (tx1 + width) % width
                            ty1 = (ty1 + height) % height
                            tx2 = x + sx + bx
                            ty2 = y + sy + by
                            tx2 = (tx2 + width) % width
                            ty2 = (ty2 + height) % height
                            space_dist = bx ** 2 + by ** 2
                            angle_dist = math.fabs(angle1[tx1][ty1] - angle2[tx2][ty2])
                            if angle_dist > math.pi * 2:
                                angle_dist -= math.pi * 2
                            if angle_dist < math.pi / 4:
                                cost = math.sqrt(sx ** 2 + sy ** 2)
                            else:
                                cost = 30.0
                            angle_dist **= 2
                            cost_temp += cost * math.exp(- space_dist / 64.0) * math.exp(- angle_dist / 0.25)
                    if cost_temp < cost_pixel:
                        cost_pixel = cost_temp
            cost_total += gray1[x][y] * cost_pixel 
    return cost_total
    
def test():
    query = Image.open('test0.png')
    dataset = Image.open('test1.jpg')
    query = query.resize((320, 240), Image.ANTIALIAS)
    query = query.filter(ImageFilter.FIND_EDGES).convert('L')
    print(distance(query, dataset))
    
    
if __name__ == '__main__':
    test()