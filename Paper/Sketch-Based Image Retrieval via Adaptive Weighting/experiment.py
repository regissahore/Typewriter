import os
from PIL import Image, ImageFilter
import distance

QUERY_DIR = 'sketches'
DATA_DIR = 'edge'
RESULT_DIR = 'dist'

for query_name in os.listdir(QUERY_DIR):
    query_path = os.path.join(QUERY_DIR, query_name)
    query_image = Image.open(query_path)
    #query_image = query_image.resize((320, 240), Image.ANTIALIAS)
    query_image = query_image.resize((160, 120), Image.ANTIALIAS)
    query_image = query_image.filter(ImageFilter.FIND_EDGES).convert('L')
    print(query_name[:-4])
    if not os.path.exists(RESULT_DIR):
        os.makedirs(RESULT_DIR)
    file = open(os.path.join(RESULT_DIR, query_name[:-4]), 'w')
    count = 0
    for data_dir in os.listdir(DATA_DIR):
        data_path = os.path.join(DATA_DIR, data_dir)
        for image_name in os.listdir(data_path):
            image_path = os.path.join(data_path, image_name)
            dataset_image = Image.open(image_path)
            dataset_image = dataset_image.resize((160, 120), Image.ANTIALIAS)
            dist = distance.distance(query_image, dataset_image)
            dist *= distance.distance(dataset_image, query_image)
            file.write(image_name[:-4] + ' ' + str(dist) + '\n')
            count += 1
            print(str(count) + '/1240 ' + image_name[:-4] + ' ' + str(dist))
    file.close()