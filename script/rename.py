# -*- coding: utf-8 -*- 

import os

def rename(rootDir):
    for dir in os.listdir(rootDir):
        path = os.path.join(rootDir, dir)
        if os.path.isdir(path):
            rename(path)
        else:
            if path[-2:] != '.h' and path[-4:] != '.cpp':
                continue
            print(dir)
            os.rename(path, os.path.join(rootDir, input()))
            
removeComment("go/include")
removeComment("go/src")