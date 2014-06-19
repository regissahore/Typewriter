from random import randint, uniform
from math import sqrt
from PIL import Image, ImageDraw

def get_dist1(x1, y1, x2, y2):
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)
    
def get_dist2(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)
    
def get_dist3(x1, y1, x2, y2):
    return max(abs(x1 - x2), abs(y1 - y2))
    
def get_dist(x1, y1, x2, y2):
    return get_dist3(x1, y1, x2, y2)

center = [(randint(0, 255), randint(0, 255)) for _ in range(7)]
color = [(237, 28, 36), (255, 127, 39), (34, 177, 76), (63, 72, 204), (163, 73, 164),
         (0, 162, 232), (185, 122, 87)]
pixel = [[center[i] for j in range(5000)] for i in range(7)]
for k in range(1000):
    print k
    image = Image.new('RGB', (256, 256), color=(255, 255, 255))
    draw = ImageDraw.Draw(image)
    for i in range(7):
        cx, cy = center[i]
        draw.rectangle((cx - 2, cy - 2, cx + 3, cy + 3), fill=color[i])
        for j in range(5000):
            x, y = pixel[i][j]
            origin_dist = get_dist(x, y, cx, cy)
            x += randint(-5, 5)
            y += randint(-5, 5)
            dist = get_dist(x, y, cx, cy)
            flag = True
            if x < 0 or x >= 256 or y < 0 or y >= 256:
                flag = False
            if flag:
                for ii in range(7):
                    if i != ii:
                        tx, ty = center[ii]
                        temp_dist = get_dist(x, y, tx, ty)
                        if temp_dist < dist:
                            flag = False
                            break
            if flag:
                if dist >= origin_dist:
                    if randint(1, 100) > 45:
                        pixel[i][j] = (x, y)
                        origin_dist = dist
                else:
                    if randint(1, 100) > 55:
                        pixel[i][j] = (x, y)
            x, y = pixel[i][j]
            draw.rectangle((x, y, x + 1, y + 1), fill=color[i])
    image.save('grid' + str(k) + '.jpg', 'JPEG')
    