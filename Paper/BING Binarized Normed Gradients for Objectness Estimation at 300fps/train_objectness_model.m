function train_objectness_model()
    setting = get_setting();
    if ~exist(setting.train.bing, 'dir')
        mkdir(setting.train.bing);
    end
    load(setting.model_a_file, 'a', 'beta');
    load(setting.model_w_file, 'model');
    files = dir(setting.train.image);
    sizes = setting.sizes;
    size_num = length(sizes);
    v = zeros([size_num, size_num]);
    t = zeros([size_num, size_num]);
    s = cell([size_num, size_num]);
    o = cell([size_num, size_num]);
    for i = 1 : size_num
        for j = 1 : size_num
            s{i, j} = [];
            o{i, j} = [];
        end
    end
    for i = 1 : length(files)
        file_name = files(i).name;
        if file_name(1) == '.'
            continue;
        end
        truth_path = [setting.train.annotation, file_name(1 : length(file_name) - 4), '.xml'];
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
        image_path = [setting.train.image, file_name];
        image = imread(image_path);
        height = size(image, 1);
        width = size(image, 2);
        for hi = 1 : size_num
            h = sizes(hi);
            hs = height / h;
            for wi = 1 : size_num
                w = sizes(wi);
                ws = width / w;
                disp([w, h]);
                bing_path = [setting.train.bing, file_name, '_', num2str(w), '_', num2str(h), '.mat'];
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
                score_path = [setting.train.bing, file_name, '_', num2str(w), '_', num2str(h), '_score.mat'];
                if exist(score_path, 'file')
                    load(score_path, 'score', 'objectness');
                else
                    for y = 1 : h - 7
                        for x = 1 : w - 7
                            sub_bing(:, :) = bing(y + 7, x + 7, :, :);
                            score(y, x) = sum(get_filter_score(sub_bing, a, beta));
                            objectness(y, x) = 0.0;
                            for k = 1 : size(truth_rects, 1)
                                int_union_score = intersect_union_score([x * ws, y * hs, 8 * ws, 8 * hs], reshape(truth_rects(k, :), [4, 1]));
                                if int_union_score > objectness(y, x)
                                    objectness(y, x) = int_union_score;
                                end
                            end
                        end
                    end
                    save(score_path, 'score', 'objectness');
                end
                for y = 1 : h - 7
                    for x = 1 : w - 7
                        if objectness(y, x) < 0.05
                            continue;
                        end
                        if x > 1 && objectness(y, x) < objectness(y, x - 1)
                            continue;
                        end
                        if x < w - 7 && objectness(y, x) < objectness(y, x + 1)
                            continue;
                        end
                        if y > 1 && objectness(y, x) < objectness(y - 1, x)
                            continue;
                        end
                        if y < h - 7 && objectness(y, x) < objectness(y + 1, x)
                            continue;
                        end
                        s{hi, wi}(length(s{hi, wi}) + 1) = score(y, x);
                        o{hi, wi}(length(o{hi, wi}) + 1) = objectness(y, x);
                    end
                end
                disp(['Data num: ', num2str(length(s{hi, wi}))]);
                if length(s{hi, wi}) > 0
                    sm = mean(s{hi, wi});
                    om = mean(o{hi, wi});
                    ss = s{hi, wi} - sm;
                    os = o{hi, wi} - om;
                    v(hi, wi) = sum(ss .* os) / sum(ss .* ss);
                    t(hi, wi) = om - v(hi, wi) * sm;
                    subplot(size_num, size_num, (hi - 1) * size_num + wi);
                    x = min(s{hi, wi}) : 0.01 : max(s{hi, wi});
                    y = v(hi, wi) .* x + t(hi, wi);
                    r = randperm(length(s{hi, wi}), min([length(s{hi, wi}), 100]));
                    % scatter(s{hi, wi}(r), o{hi, wi}(r), '.');
                    % axis([min(s{hi, wi}) - 0.01 max(s{hi, wi}) + 0.01 0 1]);
                    % hold on;
                    plot(x, y);
                    % hold off;
                    axis([-1 1 0 1]);
                    xlabel('s');
                    ylabel('o');
                    drawnow;
                end
            end
        end
        save(setting.model_o_file, 'v', 't');
    end
end