disp('Testing');
setting = get_setting();
files = dir(setting.test.image);
if ~exist(setting.test.result, 'dir')
    mkdir(setting.test.result);
end
if ~exist(setting.test.bing, 'dir')
    mkdir(setting.test.bing);
end
sizes = setting.sizes;
size_num = length(sizes);
load(setting.model_a_file, 'a', 'beta');
% load(setting.model_w_file, 'model');
load(setting.model_o_file, 'v', 't');
for i = 1 : length(files)
    file_name = files(i).name;
    if file_name(1) == '.'
        continue;
    end
    sub_bing = uint64(zeros([setting.Ng, 3]));
    disp(file_name);
    file_path = strcat(setting.test.image, file_name);
    result_path = strcat(setting.test.result, strcat(file_name(1 : (length(file_name) - 4)), '.xml'));
    image = imread(file_path);
    height = size(image, 1);
    width = size(image, 2);
    candidates = [];
    candidate_num = 0;
    for hi = 1 : size_num
        h = sizes(hi);
        hs = height / h;
        for wi = 1 : size_num
            w = sizes(wi);
            ws = width / w;
            disp([w, h]);
            bing_path = strcat(setting.test.bing, [file_name, '_', num2str(w), '_', num2str(h), '.mat']);
            if exist(bing_path, 'file')
                load(bing_path, 'ng', 'bing');
                disp('Loaded');
            else
                sub = imresize(image, [h, w]);
                ng = normed_gradient(sub);
                bing = binary_normed_gradient(ng);
                save(bing_path, 'ng', 'bing');
                disp('Binaried');
            end
            score_path = strcat(setting.test.bing, [file_name, '_', num2str(w), '_', num2str(h), '_score.mat']);
            if exist(score_path, 'file')
                load(score_path, 'score');
            else
                for y = 1 : h - 7
                    for x = 1 : w - 7
                        sub_bing(:, :) = bing(y + 7, x + 7, :, :);
                        score(y, x) = sum(get_filter_score(sub_bing, a, beta)) * v(hi, wi) + t(hi, wi);
                        % score(y, x) = sum(model(:, 1) .* reshape(double(ng(y : y + 7, x : x + 7, 1)), [64, 1]));
                    end
                end
                save(score_path, 'score');
            end
            for y = 1 : h - 7
                for x = 1 : w - 7
                    if x > 1 && score(y, x) < score(y, x - 1)
                        continue;
                    end
                    if x < w - 7 && score(y, x) < score(y, x + 1)
                        continue;
                    end
                    if y > 1 && score(y, x) < score(y - 1, x)
                        continue;
                    end
                    if y < h - 7 && score(y, x) < score(y + 1, x)
                        continue;
                    end
                    candidate_num = candidate_num + 1;
                    candidates(candidate_num, 1 : 5) = [x * ws, y * hs, 8 * ws, 8 * hs, score(y, x)];
                end
            end
        end
    end
    disp(['Sorting', '_', num2str(candidate_num)]);
    candidates = sortrows(candidates, -5);
    for j = 1 : 50
        image_path = [setting.test.bing, file_name, '_', num2str(j), '.jpg'];
        sub = imcrop(image, floor([candidates(j, 1), candidates(j, 2), candidates(j, 3), candidates(j, 4)]));
        imwrite(sub, image_path, 'jpg');
        image_path = [setting.test.bing, file_name, '_', num2str(j), '_ng.jpg'];
        ng = normed_gradient(sub);
        imwrite(imresize(ng, [8, 8]), image_path, 'jpg');
    end
    fid = fopen(result_path, 'w');
    for j = 1 : min([setting.proposal_num, candidate_num])
        fprintf(fid, '%d %d %d %d\n', floor(candidates(j, 1 : 4)));
    end
    fclose(fid);
end
disp('Finished');