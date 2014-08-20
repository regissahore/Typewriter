import os
import Image

ROOT_DIR = 'images'
THUMB_DIR = 'thumb'
for dir_name in os.listdir(ROOT_DIR):
    dir_path = os.path.join(ROOT_DIR, dir_name)
    thumb_path = os.path.join(THUMB_DIR, dir_name)
    if not os.path.exists(thumb_path):
        os.makedirs(thumb_path)
    for image_name in os.listdir(dir_path):
        image_path = os.path.join(dir_path, image_name)
        image = Image.open(image_path)
        image = image.resize((320, 240), Image.ANTIALIAS)
        image.save(os.path.join(thumb_path, image_name))
        