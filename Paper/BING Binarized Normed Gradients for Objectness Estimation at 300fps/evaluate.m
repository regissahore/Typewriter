setting = get_setting();
files = dir(setting.test.result);
detect_rate = zeros([1, setting.proposal_num]);
truth_num = 0;
rect1 = zeros([1, 4]);
rect2 = zeros([1, 4]);
if ~exist(setting.evaluate, 'dir')
    mkdir(setting.evaluate);
end
for i = 1 : length(files)
    file_name = files(i).name;
    if file_name(1) == '.'
        continue;
    end
    result_path = strcat(setting.test.result, file_name);
    truth_path = strcat(setting.test.annotation, file_name);
    result_rects = [];
    fid = fopen(result_path, 'r');
    for j = 1 : setting.proposal_num
        [rect, count] = fscanf(fid, '%d', 4);
        if count ~= 4
            break;
        end
        result_rects(size(result_rects, 1) + 1, 1 : 4) = rect;
    end
    fclose(fid);
    truth_rects = [];
    fid = fopen(truth_path, 'r');
    while true
        [rect, count] = fscanf(fid, '%d', 4);
        if count ~= 4
            break;
        end
        truth_rects(size(truth_rects, 1) + 1, 1 : 4) = rect;
    end
    fclose(fid);
    cnt = 0;
    truth_num = truth_num + size(truth_rects, 1);
    for j = 1 : min([setting.proposal_num, size(result_rects, 1)])
        if j <= length(result_rects)
            for k = 1 : size(truth_rects, 1)
                rect1(:) = result_rects(j, :);
                rect2(:) = truth_rects(k, :);
                if intersect_union_score(rect1, rect2) > 0.5
                    cnt = cnt + 1;
                    truth_rects(k, :) = [-1000, -1000, 1000, 1000];
                    break;
                end
            end
        end
        detect_rate(j) = detect_rate(j) + cnt;
    end
    for j = min([setting.proposal_num, size(result_rects, 1)]) + 1 : setting.proposal_num
        detect_rate(j) = detect_rate(j) + cnt;
    end
    if false
        truth_rects = [];
        fid = fopen(truth_path, 'r');
        while true
            [rect, count] = fscanf(fid, '%d', 4);
            if count ~= 4
                break;
            end
            truth_rects(size(truth_rects, 1) + 1, 1 : 4) = rect;
        end
        fclose(fid);
        image_path = [setting.test.image, file_name(1 : length(file_name) - 4), '.jpg'];
        image = imread(image_path);
        for k = 1 : size(truth_rects, 1)
            max_int = -1.0;
            index = 0;
            rect2(:) = truth_rects(k, :);
            for j = 1 : min([setting.proposal_num, size(result_rects, 1)])
                rect1(:) = result_rects(j, :);
                if intersect_union_score(rect1, rect2) > max_int
                    max_int = intersect_union_score(rect1, rect2);
                    index = j;
                end
            end
            rect1(:) = result_rects(index, :);
            save_path_truth = [setting.evaluate, file_name(1 : length(file_name) - 4), '_', num2str(k), '_truth.jpg'];
            save_path_result = [setting.evaluate, file_name(1 : length(file_name) - 4), '_', num2str(k), '_result.jpg'];
            sub = imcrop(image, rect1);
            imwrite(sub, save_path_result, 'jpg');
            sub = imcrop(image, rect2);
            imwrite(sub, save_path_truth, 'jpg');
        end
    end
end
detect_rate = detect_rate ./ truth_num;
save(setting.result_dr_file, 'detect_rate');
plot(1 : setting.proposal_num, detect_rate);
% semilogx(1 : setting.proposal_num, detect_rate);