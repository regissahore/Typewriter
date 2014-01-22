# -*- coding: utf-8 -*- 

import os
import codecs

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
            print()
            
# rename("go/include")

nameList = []

def get_name_list(rootDir):
    global nameList
    for dir in os.listdir(rootDir):
        path = os.path.join(rootDir, dir)
        if os.path.isdir(path):
            get_name_list(path)
        else:
            if path[-2:] != '.h':
                continue
            nameList.append(dir[:-2])
            
get_name_list("go/include")

def rename_by_include(rootDir):
    global nameList
    for dir in os.listdir(rootDir):
        path = os.path.join(rootDir, dir)
        if os.path.isdir(path):
            rename_by_include(path)
        else:
            if path[-4:] != '.cpp':
                continue
            for name in nameList:
                if name.lower() == dir[:-4]:
                    os.rename(path, os.path.join(rootDir, name + ".cpp"))
                    break
            
# rename_by_include("go/src")

def rename_in_file(rootDir):
    global nameList
    for dir in os.listdir(rootDir):
        path = os.path.join(rootDir, dir)
        if os.path.isdir(path):
            rename_in_file(path)
        else:
            if path[-2:] != '.h' and path[-4:] != '.cpp':
                continue
            print(path)
            file = codecs.open(path, 'r', 'utf-8')
            content = file.readlines()
            file.close()
            file = codecs.open(path, 'w', 'utf-8')
            for line in content:
                print(content[:8])
                if content[:8] == "#include":
                    newLine = content[9:-2]
                    print(newLine)
                    for name in nameList:
                        if name.lower() == newLine:
                            newLine = "#include \"" + name + "\""
                            break
            file.close()
                    
rename_in_file("go")