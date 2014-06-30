% Contants.
DATA_TYPE = {'train/', 'val/', 'test/'};
FOLDER_DATA = 'data/images/';
FOLDER_TRUTH = 'data/truth/';
FOLDER_FEATURE = 'data/feature/';
FOLDER_EDGE = 'data/edge/';
TREE_NAME = 'tree_';

PATCH_NUM = 20000;
PATCH_SIZE = 16;
TREE_NUM = 5;

% Extract features.
if ~exist('feature.step', 'file')
    if ~exist(FOLDER_FEATURE, 'dir')
        mkdir(FOLDER_FEATURE);
    end
    for t = 1 : length(DATA_TYPE)
        data_type = DATA_TYPE{t};
        data_folder = strcat(FOLDER_DATA, data_type);
        feature_folder = strcat(FOLDER_FEATURE, data_type);
        if ~exist(feature_folder, 'dir')
            mkdir(feature_folder);
        end
        files = dir(data_folder);
        for f = 1 : length(files)
            file = files(f).name;
            if file(1) == '.'
                continue
            end
            file_path = strcat(data_folder, file);
            feature_path = strcat(feature_folder, strcat(file(1 : length(file) - 4), '.mat'));
            disp(file_path);
            image = imread(file_path);
            feature = extract(image);
            save(feature_path, 'feature');
        end
    end
    file = fopen('feature.step', 'w');
    fclose(file);
end

% Build trees.
for t = 1 : TREE_NUM
    tree_name = strcat(strcat(TREE_NAME, num2str(t)), '.mat');
    disp(tree_name);
    if ~exist(tree_name, 'file')
        feature_folder = strcat(FOLDER_FEATURE, DATA_TYPE{1});
        truth_folder = strcat(FOLDER_TRUTH, DATA_TYPE{1});
        files = dir(feature_folder);
        patch_num = 0;
        feature_patches = cell(1, PATCH_NUM);
        truth_patches = cell(1, PATCH_NUM);
        while patch_num < PATCH_NUM
            if mod(patch_num, 1000) == 0
                disp(patch_num);
            end
            file_name = '';
            while 1 == 1
                file_name = files(randi([1, length(files)])).name;
                if file_name(1) ~= '.'
                    break
                end
            end
            feature_path = strcat(feature_folder, file_name);
            truth_path = strcat(truth_folder, file_name);
            load(feature_path, 'feature');
            load(truth_path, 'groundTruth');
            [height, width, ~] = size(feature);
            for i = 1 : 100
                y = randi([1, height - PATCH_SIZE + 1]);
                x = randi([1, width - PATCH_SIZE + 1]);
                patch_num = patch_num + 1;
                feature_patches{patch_num} = feature(y : y + PATCH_SIZE - 1, x : x + PATCH_SIZE - 1, :);
                truth_patches{patch_num}.segment = groundTruth{1}.Segmentation(y : y + PATCH_SIZE - 1, x : x + PATCH_SIZE - 1);
                truth_patches{patch_num}.boundary = groundTruth{1}.Boundaries(y : y + PATCH_SIZE - 1, x : x + PATCH_SIZE - 1);
                if patch_num >= PATCH_NUM
                    break
                end
            end
        end
        tree = build(feature_patches, truth_patches);
        save(tree_name, 'tree');
    end
end

% Detect edges.
feature_folder = strcat(FOLDER_FEATURE, DATA_TYPE{3});
edge_folder = strcat(FOLDER_EDGE, DATA_TYPE{3});
if ~exist(edge_folder, 'dir')
    mkdir(edge_folder);
end
files = dir(feature_folder);
for f = 1 : length(files)
    file = files(f).name;
    if file(1) == '.'
        continue
    end
    feature_path = strcat(feature_folder, file);
    edge_path = strcat(edge_folder, file);
    if exist(edge_path, 'file')
        continue
    end
    disp(edge_path);
    load(feature_path, 'feature');
    [height, width, ~] = size(feature);
    edge = zeros(height, width);
    count = zeros(height, width);
    for t = 1 : TREE_NUM
        tree_name = strcat(strcat(TREE_NAME, num2str(t)), '.mat');
        load(tree_name, 'tree');
        disp(tree_name);
        for x = 1 : width - 16 + 1
            for y = 1 : height - 16 + 1
                edge(y : y + 16 - 1, x : x + 16 - 1) = edge(y : y + 16 - 1, x : x + 16 - 1) + detect(tree, feature(y : y + 16 - 1, x : x + 16 - 1, :));
                count(y : y + 16 - 1, x : x + 16 - 1) = count(y : y + 16 - 1, x : x + 16 - 1) + 1;
            end
        end
        imwrite(edge ./ count, strcat(edge_path(1 : length(edge_path) - 4), '.jpg'), 'jpg');
    end
    edge = edge ./ count;
    save(edge_path, 'edge');
end
for f = 1 : length(files)
    file = files(f).name;
    if file(1) == '.'
        continue
    end
    edge_path = strcat(edge_folder, file);
    im = imread(strcat(edge_path(1 : length(edge_path) - 4), '.jpg'));
    im = 1.0 - double(im) / 255.0;
    imwrite(im, strcat(edge_path(1 : length(edge_path) - 4), '_i.jpg'));
end
% Validate results.