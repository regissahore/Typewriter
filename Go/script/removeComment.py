# -*- coding: utf-8 -*- 

import os
import codecs

def removeComment(rootDir):
    for dir in os.listdir(rootDir):
        path = os.path.join(rootDir, dir)
        if os.path.isdir(path):
            removeComment(path)
        else:
            if path[-2:] != '.h' and path[-4:] != '.cpp':
                continue
            print(path)
            file = codecs.open(path, 'r', 'utf-8')
            content = file.readlines()
            file.close()
            isComment = False
            file = codecs.open(path, 'w', 'utf-8')
            for line in content:
                if not isComment:
                    if line[:3] == "/**":
                        isComment = True
                    else:
                        file.write(line)
                if isComment:
                    if line[-3:] == "*/\n":
                        isComment = False
            file.close()
            
removeComment("tm")