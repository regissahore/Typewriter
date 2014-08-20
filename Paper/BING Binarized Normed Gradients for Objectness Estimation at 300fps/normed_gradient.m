function ng_feature = normed_gradient(image)
    ng_feature = zeros(size(image));
    for k = 1 : size(image, 3)
        ng_feature(:, :, k) = ng_feature(:, :, k) + abs(imfilter(double(image(:, :, k)), [-1, 0, 1]));
        ng_feature(:, :, k) = ng_feature(:, :, k) + abs(imfilter(double(image(:, :, k)), [-1; 0; 1]));
        ng_feature(:, :, k) = ng_feature(:, :, k) .* (ng_feature(:, :, k) < 256);
    end
    ng_feature = uint8(ng_feature);
end