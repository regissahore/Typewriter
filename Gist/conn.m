for i = 0 : 295
    name = sprintf('grid%d.jpg', i);
    im = imread(name);
    [I, map] = rgb2ind(im, 20);
    if i == 0
        imwrite(I, map, 'res.gif', 'gif', 'Loopcount', inf, 'DelayTime', 0.01);
    else
        imwrite(I, map, 'res.gif', 'gif', 'WriteMode', 'append', 'DelayTime', 0.01);
    end
end
for i = 0 : 50
    imwrite(I, map, 'res.gif', 'gif', 'WriteMode', 'append', 'DelayTime', 0.01);
end