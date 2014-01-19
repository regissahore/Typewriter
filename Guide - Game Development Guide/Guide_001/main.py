# coding: utf-8
# 这部分考虑的是对键盘操作的响应和对墙壁与地面的碰撞检测。
# 所有物体都是1×1单位的正方体，而操控对象是2×1单位的长方体。
# 由于编程简单，这是上个世纪常见的游戏设计方式。
# 目标如下：
# 通过'A'和'D'实现操作对象的左右移动。
# 通过空格键实现操作对象的跳跃。
# 对所有背景的碰撞检测。
import sys
import pygame
import pygame.draw
from pygame.locals import *

# 窗口的大小
WINDOW_WIDTH = 640
WINDOW_HEIGHT = 480

# 单位的大小，所以窗口内如果紧密地放置有15×20个单位。
UNIT_SIZE = 32

# 背景单位的数组。
background = []

# 初始化背景单位，由1×1的单位构成。
# 为了使用函数外的变量需要用global声明。
def initBackground():
    global background
    for i in range(0, 20):
        for j in range(0, 15):
            if i == 0 or j == 0 or i == 19 or j == 14:
                block = {}
                block['x'] = i * UNIT_SIZE
                block['y'] = j * UNIT_SIZE
                background.append(block)
    for j in range(14, 0, -1):
        for i in range((14 - j) * 3 + 5, 20):
            block = {}
            block['x'] = i * UNIT_SIZE
            block['y'] = j * UNIT_SIZE
            background.append(block)

# 绘制背景。
# 注意绘制矩形的操作，第二个参数为RGB的颜色，第三个参数为矩形的左上角坐标和矩形的长宽。
def drawBackground(surface):
    global background
    pygame.draw.rect(surface, (0, 0, 0), (0, 0, WINDOW_WIDTH, WINDOW_HEIGHT))
    for block in background:
        pygame.draw.rect(surface, (0, 0, 255), (block['x'], block['y'], UNIT_SIZE, UNIT_SIZE))

player = {}        
       
# 初始化主角。由于主角的长宽已经确定，我们需要的只是主角的左上角的位置信息。
# 这里我们用global的player变量记录主角的位置，设置map映射可以参考背景初始化所使用的方式。
# 我们将主角的位置设定为(64, 383)。
# 同时我们将设定主角当前的x方向速度和y方向速度都为0。
def initPlayer():
    global player
    # Guide 1
    # 目标：初始化主角
   
# 主角的绘制，为了方便区分要使用一个和背景色不同的颜色。
# 可以参考背景的绘制方式。
def drawPlayer(surface):
    global player
    # Guide 2
    # 目标：绘制主角
    
# 操纵主角水平移动，移动速度可以为0.2。
def horizonMove():
    pressed = pygame.key.get_pressed()
    if pressed[K_a]:
        player['speedX'] = -0.2
    # Guide 3
    # 目标：向右的移动速度
    # Guide 4
    # 目标：未知
        
# 水平移动主角，将主角的左上角坐标加上运动速度即可。
# 虽然通常不应该这么做。
def playerMoveHorizon():
    global player
    # Guide 5
    # 目标：水平移动主角
   
# 垂直移动主角，将主角的左上角坐标加上运动速度即可。   
def playerMoveVertical():
    global player
    # Guide 6
    # 目标：垂直移动主角

# 水平碰撞检测，可以参考绘制背景是枚举背景的方法。
# 如果操控的矩形将要移动到的位置与所有背景矩形都没有交集，则认为可以移动，这时可以return False。
# 逻辑“与”和“或”使用的是and和or。
# 检查矩形是否有交集的方法可以自己搜索一下。
# 实际上，对于本例有一个简单的实现方式。
def hitDetectionHorizon():
    global player
    global background
    # Guide 7
    # 目标：水平方向碰撞检测
    return False
    
# 垂直碰撞检测，可以参考绘制背景是枚举背景的方法。
# 如果操控的矩形将要移动到的位置与所有背景矩形都没有交集，则认为可以移动，这时可以return False。
# 逻辑“与”和“或”使用的是and和or。
# 检查矩形是否有交集的方法可以自己搜索一下。
# 实际上，对于本例有一个简单的实现方式。
def hitDetectionVertical():
    global player
    global background
    # Guide 8
    # 目标：垂直方向碰撞检测
    return True
    
# 重力，主角每时每刻都在重力场的影响下，可以考虑加速度为0.03。
# 注意限制最大速度。
def gravity():
    global player
    # Guide 9
    # 目标：添加重力

# 跳跃，可以考虑将速度设为3。        
def jump():
    global player
    # Guide 10
    # 目标：跳跃
        
# 游戏主循环
def gameLoop():
    pygame.init()
    surface = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT), 0, 32)
    pygame.display.set_caption('Guide 1')
    
    initBackground()
    initPlayer()

    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == KEYDOWN:
                if event.key == K_SPACE:
                    jump()
        drawBackground(surface)
        drawPlayer(surface)
        horizonMove()
        gravity()
        if not hitDetectionHorizon():
            playerMoveHorizon()
        if not hitDetectionVertical():
            playerMoveVertical()
        pygame.display.update()
    
if __name__ == "__main__":
    gameLoop()