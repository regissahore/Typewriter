function [tree, finished] = build(feature_patches, truth_patches)
    disp('build');
    disp(length(feature_patches));
    n = length(feature_patches);
    if length(feature_patches) == 1
        tree.type = 0;
        tree.segment = truth_patches{1}.segment;
        tree.boundary = truth_patches{1}.boundary;
        finished = 1;
    else
        subset = zeros(256, length(feature_patches));
        for k = 1 : 256
            x1 = randi([1, 16]);
            y1 = randi([1, 16]);
            x2 = randi([1, 16]);
            y2 = randi([1, 16]);
            if n >= 10000
                disp(k);
            end
            for i = 1 : n
                subset(k, i) = truth_patches{i}.segment(x1, y1) == truth_patches{i}.segment(x2, y2);
            end
        end
        disp('pca');
        u = pca(subset);
        disp(size(u, 2));
        if size(u, 2) == 0
            class = randi([0 1], 1, n);
        else
            subset = u(:, 1)' * subset;
            subset = subset + rand(1, length(subset)) / 1e6;
            class = subset > median(subset);
        end
        best = 1e10;
        unchange = 0;
        if n < 10
            max_unchange = 10000;
            step = 0.0001;
        elseif n < 100
            max_unchange = 1000;
            step = 0.001;
        elseif n < 1000
            max_unchange = 100;
            step = 0.01;
        elseif n < 10000
            max_unchange = 10;
            step = 0.1;
        else
            max_unchange = 3;
            step = 0.1;
        end
        while unchange < max_unchange
            unchange = unchange + 1;
            if mod(unchange, 1) == 0
                disp(unchange);
            end
            k = randi([1 2]);
            x = randi([1 16]);
            y = randi([1 16]);
            type = randi([1 2]);
            if type == 1
                for tau = 0.0 : step : 1.0
                    [cntL0, cntL1, cntR0, cntR1] = count_1(feature_patches, class, k, x, y, tau);
                    score = get_score(cntL0, cntL1, cntR0, cntR1);
                    if score < best
                        disp([score, cntL0, cntL1, cntR0, cntR1]);
                        best = score;
                        tree.type = 1;
                        tree.x = x;
                        tree.y = y;
                        tree.k = k;
                        tree.tau = tau;
                        unchange = 0;
                    end
                end
            else
                xx = randi([1 16]);
                yy = randi([1 16]);
                for tau = 0.0 : step : 1.0
                    [cntL0, cntL1, cntR0, cntR1] = count_2(feature_patches, class, k, x, y, xx, yy, tau);
                    score = get_score(cntL0, cntL1, cntR0, cntR1);
                    if score < best
                        disp([score, cntL0, cntL1, cntR0, cntR1]);
                        best = score;
                        tree.type = 2;
                        tree.k = k;
                        tree.x1 = x;
                        tree.y1 = y;
                        tree.x2 = xx;
                        tree.y2 = yy;
                        tree.tau = tau;
                        unchange = 0;
                    end
                end
            end
            if best < 1e-4
                break
            end
        end
        left_num = 0;
        right_num = 0;
        feature_left = cell(1, n);
        truth_left = cell(1, n);
        feature_right = cell(1, n);
        truth_right = cell(1, n);
        for i = 1 : n
            if tree.type == 1
                decision = feature_patches{i}(tree.x, tree.y, tree.k) > tree.tau;
            else
                decision = feature_patches{i}(tree.x1, tree.y1, tree.k) - feature_patches{i}(tree.x2, tree.y2, tree.k) > tree.tau;
            end
            if decision == 0
                left_num = left_num + 1;
                feature_left{left_num} = feature_patches{i};
                truth_left{left_num} = truth_patches{i};
            else
                right_num = right_num + 1;
                feature_right{right_num} = feature_patches{i};
                truth_right{right_num} = truth_patches{i};
            end
        end
        if left_num == 0 || right_num == 0
            tree.type = 3;
            while abs(left_num - right_num) > 1
                if left_num > right_num
                    right_num = right_num + 1;
                    feature_right{right_num} = feature_left{left_num};
                    truth_right{right_num} = truth_left{left_num};
                    left_num = left_num - 1;
                else
                    left_num = left_num + 1;
                    feature_left{left_num} = feature_right{right_num};
                    truth_left{left_num} = truth_right{right_num};
                    right_num = right_num - 1;
                end
            end
        end
        [tree.left, finished_left] = build(feature_left(1 : left_num), truth_left(1 : left_num));
        [tree.right, finished_right] = build(feature_right(1 : right_num), truth_right(1 : right_num));
        finished = finished_left + finished_right;
        disp('finished');
        disp(finished);
    end
end

function [entropy] = get_entropy(a, b)
    if a == 0 || b == 0
        entropy = 0.0;
    else
        p = a / (a + b);
        entropy = - p * log(p) - (1 - p) * log(1 - p);
    end
end

function [score] = get_score(cntL0, cntL1, cntR0, cntR1)
    alpha = (cntL0 + cntL1) / (cntL0 + cntL1 + cntR0 + cntR1);
    score = alpha * get_entropy(cntL0, cntL1) + (1.0 - alpha) * get_entropy(cntR0, cntR1);
end

function [cntL0, cntL1, cntR0, cntR1] = count_1(feature_patches, class, k, x, y, tau)
    cntL0 = 0;
    cntL1 = 0;
    cntR0 = 0;
    cntR1 = 0;
    parfor i = 1 : length(feature_patches)
        if feature_patches{i}(x, y, k) < tau
            if class(i) == 0
                cntL0 = cntL0 + 1;
            else
                cntL1 = cntL1 + 1;
            end
        else
            if class(i) == 0
                cntR0 = cntR0 + 1;
            else
                cntR1 = cntR1 + 1;
            end
        end
    end
end

function [cntL0, cntL1, cntR0, cntR1] = count_2(feature_patches, class, k, x1, y1, x2, y2, tau)
    cntL0 = 0;
    cntL1 = 0;
    cntR0 = 0;
    cntR1 = 0;
    parfor i = 1 : length(feature_patches)
        if feature_patches{i}(x1, y1, k) - feature_patches{i}(x2, y2, k) < tau
            if class(i) == 0
                cntL0 = cntL0 + 1;
            else
                cntL1 = cntL1 + 1;
            end
        else
            if class(i) == 0
                cntR0 = cntR0 + 1;
            else
                cntR1 = cntR1 + 1;
            end
        end
    end
end