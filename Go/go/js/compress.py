# coding=utf-8
import os
import codecs

def isEmpty(ch):
    return ch == ' ' or ch == '\t'
    
path = os.path.abspath(os.curdir)
for fileName in os.listdir(path):
    if fileName[0:9] == "compress_":
        continue
    file = codecs.open(fileName, 'r', 'utf-8')
    content = file.readlines();
    file.close();
    file = codecs.open("compress_" + fileName, 'w', 'utf-8')
    lastCh = 0
    for line in content:
        for ch in line:
            if isEmpty(ch) and isEmpty(lastCh):
                continue
            if ch == "\n" or ch == "\r":
                lastCh = ' '
                continue
            lastCh = ch
            file.write(lastCh)
    file.close()