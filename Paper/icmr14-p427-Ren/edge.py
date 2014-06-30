import os
from PIL import Image, ImageFilter

ROOT_DIR = 'thumb'
EDGE_DIR = 'edge'
for dir_name in os.listdir(ROOT_DIR):
    dir_path = os.path.join(ROOT_DIR, dir_name)
    edge_path = os.path.join(EDGE_DIR, dir_name)
    if not os.path.exists(edge_path):
        os.makedirs(edge_path)
    for image_name in os.listdir(dir_path):
        image_path = os.path.join(dir_path, image_name)
        image = Image.open(image_path)
        image = image.filter(ImageFilter.SMOOTH_MORE)
        image = image.filter(ImageFilter.FIND_EDGES).convert('L')
        image.save(os.path.join(edge_path, image_name))