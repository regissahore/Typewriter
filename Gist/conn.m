for i = 0 : 260
    name = sprintf('grid%d.jpg', i);
    im = imread(name);
    [I, map] = rgb2ind(im, 20);
    if i == 0
        imwrite(I, map, 'res.gif', 'gif', 'Loopcount', inf, 'DelayTime', 0.1);
    else
        imwrite(I, map, 'res.gif', 'gif', 'WriteMode', 'append', 'DelayTime', 0.1);
    end
end
for i = 259 : -1 : 1
    name = sprintf('grid%d.jpg', i);
    im = imread(name);
    [I, map] = rgb2ind(im, 20);
    imwrite(I, map, 'res.gif', 'gif', 'WriteMode', 'append', 'DelayTime', 0.1);
end