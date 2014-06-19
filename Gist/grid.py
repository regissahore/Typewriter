from PIL import Image, ImageDraw
from math import sqrt

GRID_SIZE = 32
RECT_WIDTH = 16

grid = [[' ' for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
isNew = False
cur = 0
k = 0
cnt = 0
image = Image.new('RGB', (GRID_SIZE * RECT_WIDTH, GRID_SIZE * RECT_WIDTH), color=(255, 255, 255))
draw = ImageDraw.Draw(image)
while True:
    if not isNew:
        cx = int(k * (sqrt(5.0) + 1.0) * 0.5);
        cy = cx + k;
        if cy >= GRID_SIZE:
            break
        k += 1
        grid[cx][cy] = grid[cy][cx] = 'P'
        draw.rectangle((cx * RECT_WIDTH, cy * RECT_WIDTH, (cx + 1) * RECT_WIDTH, (cy + 1) * RECT_WIDTH), fill = (0, 0, 0))
        draw.rectangle((cy * RECT_WIDTH, cx * RECT_WIDTH, (cy + 1) * RECT_WIDTH, (cx + 1) * RECT_WIDTH), fill = (0, 0, 0))
        cur = 1
        isNew = True
        if k % 2 == 0:
            color = (200, 200, 200)
        else:
            color = (150, 150, 150)
        continue
    isNew = False
    if cx + cur < GRID_SIZE:
        grid[cx + cur][cy] = 'N'
        grid[cy][cx + cur] = 'N'
        x = cx + cur
        y = cy
        draw.rectangle((x * RECT_WIDTH, y * RECT_WIDTH, (x + 1) * RECT_WIDTH, (y + 1) * RECT_WIDTH), fill = color)
        draw.rectangle((y * RECT_WIDTH, x * RECT_WIDTH, (y + 1) * RECT_WIDTH, (x + 1) * RECT_WIDTH), fill = color)
        isNew = True
        if cy + cur < GRID_SIZE:
            grid[cx + cur][cy + cur] = 'N'
            grid[cy + cur][cx + cur] = 'N'
            x = cx + cur
            y = cy + cur
            draw.rectangle((x * RECT_WIDTH, y * RECT_WIDTH, (x + 1) * RECT_WIDTH, (y + 1) * RECT_WIDTH), fill = color)
            draw.rectangle((y * RECT_WIDTH, x * RECT_WIDTH, (y + 1) * RECT_WIDTH, (x + 1) * RECT_WIDTH), fill = color)
    if cy + cur < GRID_SIZE:
        grid[cx][cy + cur] = 'N'
        grid[cy + cur][cx] = 'N'
        x = cx
        y = cy + cur
        draw.rectangle((x * RECT_WIDTH, y * RECT_WIDTH, (x + 1) * RECT_WIDTH, (y + 1) * RECT_WIDTH), fill = color)
        draw.rectangle((y * RECT_WIDTH, x * RECT_WIDTH, (y + 1) * RECT_WIDTH, (x + 1) * RECT_WIDTH), fill = color)
        isNew = True
    cur += 1
    image.save('grid' + str(cnt) + '.jpg', 'JPEG')
    cnt += 1
    
        
        
