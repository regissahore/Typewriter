import os

DATA_DIR = 'edge'
RESULT_DIR = 'dist'
PRECISION_DIR = 'precision'

image_class = dict()
for dir_name in os.listdir(DATA_DIR):
    dir_path = os.path.join(DATA_DIR, dir_name)
    for image_name in os.listdir(dir_path):
        image_class[image_name[:-4]] = dir_name
for result_name in os.listdir(RESULT_DIR):
    result_path = os.path.join(RESULT_DIR, result_name)
    names = []
    dists = []
    for line in open(result_path, 'r'):
        data = line[:-1].split(' ')
        name = data[0]
        dist = float(data[1])
        names.append(name)
        dists.append(dist)
    for i in range(len(names)):
        for j in range(i + 1, len(names)):
            if dists[i] > dists[j]:
                names[i], names[j] = names[j], names[i]
                dists[i], dists[j] = dists[j], dists[i]
    precision = []
    count = 0
    for i in range(20):
        if image_class[names[i]] == result_name:
            count += 1
        precision.append(1.0 * count / (i + 1))
    if not os.path.exists(PRECISION_DIR):
        os.makedirs(PRECISION_DIR)
    precision_path = os.path.join(PRECISION_DIR, result_name)
    file = open(precision_path, 'w')
    file.write('\n'.join(map(str, precision)))
    file.close()
precision = [0.0 for i in range(20)]
count = 0
for result_name in os.listdir(PRECISION_DIR):
    precision_path = os.path.join(PRECISION_DIR, result_name)
    index = 0
    for line in open(precision_path, 'r'):
        precision[index] += float(line[:-1])
        index += 1
    count += 1
precision = [x / count for x in precision]
precision_path = os.path.join(PRECISION_DIR, 'final')
file = open(precision_path, 'w')
file.write('\n'.join(map(str, precision)))
file.close()
print(precision)
