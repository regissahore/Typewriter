# coding: utf-8
# 这是用来验证是否正确安装所需库的程序。
# 不需要理会其中的内容。
# 如果可以运行看到一个黑色的窗口库安装正常。
import sys
import pygame
from pygame.locals import *

print pygame.ver

pygame.init()
pygame.display.set_mode((640, 480), 0, 32)
pygame.display.set_caption('Test')

while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
    pygame.display.update()