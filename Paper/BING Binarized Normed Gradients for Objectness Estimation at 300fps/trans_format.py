# coding:utf-8
import os
from xml.etree import ElementTree

src_folder = ['train_xml', 'test_xml']
tar_folder = ['train_annotation', 'test_annotation']

for folder_index in range(len(src_folder)):
    src = src_folder[folder_index]
    tar = tar_folder[folder_index]
    if not os.path.exists(tar):
        os.makedirs(tar)
    cnt = 0
    for file in os.listdir(src):
        src_file_path = os.path.join(src, file)
        tar_file_path = os.path.join(tar, file)
        root = ElementTree.fromstring(open(src_file_path).read())
        tar_file = open(tar_file_path, 'w')
        bound_boxs = root.findall('object/bndbox')
        for bound_box in bound_boxs:
            cnt += 1
            x_min = bound_box.find('xmin').text
            y_min = bound_box.find('ymin').text
            x_max = bound_box.find('xmax').text
            y_max = bound_box.find('ymax').text
            width = str(int(x_max) - int(x_min))
            height = str(int(y_max) - int(y_min))
            tar_file.write(x_min + ' ' + y_min + ' ' + width + ' ' + height + '\n')
        tar_file.close()
    print cnt