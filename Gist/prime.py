from math import *
from PIL import Image, ImageDraw
IMAGE_SIZE = 256
CONTENT_SIZE = 250 / 2

prime = [True for _ in range(100000)]

for i in range(2, 100000):
    if prime[i]:
        for j in range(i + i, 100000, i):
            prime[j] = False
            
for max_num in range(100, 100000, 100):
    print max_num / 100
    image = Image.new('RGB', (IMAGE_SIZE, IMAGE_SIZE), color=(255, 255, 255))
    draw = ImageDraw.Draw(image)
    for i in range(0, max_num):
        if prime[i]:
            x = IMAGE_SIZE / 2 + i * cos(i) / max_num * CONTENT_SIZE
            y = IMAGE_SIZE / 2 + i * sin(i) / max_num * CONTENT_SIZE
            draw.rectangle((x - 1, y - 1, x + 1, y + 1), fill=(63, 72, 204))
    image.save(str(max_num / 100) + '.jpg', 'JPEG')