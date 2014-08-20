function [feature] = extract(image)
    [height, width, ~] = size(image);
    height = height - mod(height, 16);
    width = width - mod(width, 16);
    image = image(1 : height, 1 : width, :);
    feature = zeros([height, width, 2]);
    gray = rgbConvert(image, 'gray');
    luv = rgbConvert(image, 'luv');
    feature(:, :, 1) = luv(:, :, 1);
    [magnitude, ~] = gradientMag(gray, 0, 4, 0.01);
    feature(:, :, 2) = magnitude(:, :);
    gauss = fspecial('gaussian', [5, 5], 2.0);
    for i = 1 : 2
        feature(:, :, i) = filter2(gauss, feature(:, :, i));
    end
    feature = feature .* (feature > 0.0);
end
