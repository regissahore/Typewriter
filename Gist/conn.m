for i = 1 : 500
    name = sprintf('%d.jpg', i);
    im = imread(name);
    [I, map] = rgb2ind(im, 20);
    if i == 1
        imwrite(I, map, 'res.gif', 'gif', 'Loopcount', inf, 'DelayTime', 0.01);
    else
        imwrite(I, map, 'res.gif', 'gif', 'WriteMode', 'append', 'DelayTime', 0.01);
    end
end