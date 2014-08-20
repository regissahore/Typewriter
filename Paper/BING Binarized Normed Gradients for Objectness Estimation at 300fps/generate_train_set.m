function generate_train_set()
    setting = get_setting();
    if exist(setting.positive_file, 'file') && exist(setting.negative_file, 'file')
        return;
    end
    positive = {};
    negative = {};
    files = dir(setting.train.image);
    for i = 1 : length(files)
        file_name = files(i).name;
        if file_name(1) == '.'
            continue;
        end
        file_path = strcat(setting.train.image, file_name);
        annotation_path = strcat(setting.train.annotation, file_name);
        annotation_path = strcat(annotation_path(1 : (length(annotation_path) - 4)), '.xml');
        image = imread(file_path);
        fid = fopen(annotation_path, 'r');
        while true
            [rect, count] = fscanf(fid, '%d', 4);
            if count ~= 4
                break;
            end
            sub = imresize(imcrop(image, rect), [8, 8]);
            positive{length(positive) + 1} = normed_gradient(sub);
            x = randi([1, size(image, 2) - 10]);
            y = randi([1, size(image, 1) - 10]);
            width = randi([8, size(image, 2) - x - 1]);
            height = randi([8, size(image, 1) - y - 1]);
            sub = imresize(imcrop(image, [x y width height]), [8, 8]);
            negative{length(negative) + 1} = normed_gradient(sub);
        end
        fclose(fid);
    end
    save(setting.positive_file, 'positive');
    save(setting.negative_file, 'negative');
end