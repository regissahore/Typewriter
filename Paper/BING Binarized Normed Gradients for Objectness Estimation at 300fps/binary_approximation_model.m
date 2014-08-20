function binary_approximation_model()
    setting = get_setting();
    if exist(setting.model_a_file, 'file')
        return;
    end
    load(setting.model_w_file, 'model');
    a = zeros([setting.Nw, 64, 3]);
    beta = zeros([setting.Nw, 3]);
    bin = uint64(zeros([setting.Nw, 3]));
    for k = 1 : 3
        for j = 1 : setting.Nw
            a(j, :, k) = sign(model(:, k));
            beta(j, k) = sum(a(j, :, k)' .* model(:, k)) / sum(abs(a(j, :, k)));
            model(:, k) = model(:, k) - beta(j, k) * a(j, :, k)';
            for i = 1 : 64
                if a(j, i, k) > 0
                    bin(j, k) = bitor(bin(j, k), bitshift(uint64(1), 64 - i));
                end
            end
        end
    end
    figure;
    for k = 1 : setting.Nw
        subplot(1, setting.Nw, k);
        image = imresize(reshape(a(k, :, 1), [8, 8]), [128, 128], 'nearest');
        imshow(image);
    end
    a = bin;
    save(setting.model_a_file, 'a', 'beta');
end