% Contants.
DATA_TYPE = {'train/', 'val/', 'test/'};
FOLDER_DATA = 'data/images/';
FOLDER_TRUTH = 'data/truth/';

for t = 1 : length(DATA_TYPE)
    data_type = DATA_TYPE{t};
    data_folder = strcat(FOLDER_DATA, data_type);
    truth_folder = strcat(FOLDER_TRUTH, data_type);
    if ~exist(truth_folder, 'dir')
        mkdir(truth_folder);
    end
    files = dir(data_folder);
    for f = 1 : length(files)
        file = files(f).name;
        if file(1) == '.'
            continue
        end
        file_path = strcat(data_folder, file);
        edge_path = strcat(truth_folder, file);
        truth_path = strcat(truth_folder, strcat(file(1 : length(file) - 4), '.mat'));
        disp(file_path);
        image = imread(file_path);
        groundTruth = cell(1, 1);
        groundTruth{1}.Segmentation = rgb2gray(image);
        groundTruth{1}.Boundaries = edge(groundTruth{1}.Segmentation, 'canny');
        save(truth_path, 'groundTruth');
        imwrite(groundTruth{1}.Boundaries, edge_path, 'jpg');
    end
end