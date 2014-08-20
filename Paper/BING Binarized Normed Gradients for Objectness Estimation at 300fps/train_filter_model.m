function train_filter_model()
    setting = get_setting();
    if exist(setting.model_w_file, 'file')
        return;
    end
    load(setting.positive_file, 'positive');
    load(setting.negative_file, 'negative');
    label = zeros(length(positive) * 2, 1);
    data = zeros(length(positive) * 2, 64);
    model = zeros([64, 3]);
    for k = 1 : 3
        for i = 1 : length(positive)
            label(i) = 100.0;
            data(i, :) = reshape(positive{i}(:, :, k)', [1, 64]);
            label(i + length(positive)) = -100.0;
            data(i + length(positive), :) = reshape(negative{i}(:, :, k)', [1, 64]);
        end
        model_c = train_linear(label, sparse(data), '-s l1');
        model(:, k) = model_c.w(:);
    end
    save(setting.model_w_file, 'model');
    figure;
    for k = 1 : 3
        subplot(1, 3, k);
        image = (model(:, k) - min(model(:, k))) / (max(model(:, k)) - min(model(:, k)));
        image = imresize(reshape(image, [8, 8]), [128, 128], 'nearest');
        imshow(image);
    end
end