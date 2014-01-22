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
srcList = {}

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
            
# get_name_list("go/include")

def get_src_list(rootDir):
    global srcList
    for dir in os.listdir(rootDir):
        path = os.path.join(rootDir, dir)
        if os.path.isdir(path):
            get_src_list(path)
        else:
            if path[-2:] != '.h' and path[-4:] != '.cpp':
                continue
            srcList[dir] = path
            
# get_src_list("tm")

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
    global srcList
    for dir in os.listdir(rootDir):
        path = os.path.join(rootDir, dir)
        if os.path.isdir(path):
            rename_in_file(path)
        else:
            if path[-2:] != '.h' and path[-4:] != '.cpp':
                continue
            file = codecs.open(srcList[dir.lower()], 'r', 'utf-8')
            print(srcList[dir.lower()])
            content = file.readlines()
            file.close()
            file = codecs.open(path, 'w', 'utf-8')
            for line in content:
                if line[:8] == "#include":
                    newLine = line[10:-4]
                    flag = True
                    for name in nameList:
                        if name.lower() == newLine:
                            newLine = "#include \"" + name + ".h\"\n"
                            flag = False
                            break
                    if flag:
                        newLine = line
                    file.write(newLine)
                elif line[-3:] == "_H\n":
                    file.write(line)
                else:
                    file.write(line[0])
                    for i in range(1, len(line)):
                        if line[i - 1] == 'G' and line[i] == 'O':
                            file.write('o')
                        else:
                            file.write(line[i])
            file.close()
                    
# rename_in_file("go")

def generate_list(rootDir):
    global nameList
    for dir in os.listdir(rootDir):
        path = os.path.join(rootDir, dir)
        if os.path.isdir(path):
            generate_list(path)
        else:
            if path[-2:] != '.h' and path[-4:] != '.cpp':
                continue
            print("    " + path[3:] + " \\")
                    
def generate_pro_list():
    print("HEADERS += \\")
    generate_list("go/include")
    print()
    print("SOURCES += \\")
    generate_list("go/src")
    
generate_pro_list()