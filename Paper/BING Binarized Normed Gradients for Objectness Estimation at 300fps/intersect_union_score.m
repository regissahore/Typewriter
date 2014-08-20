function score = intersect_union_score(rect1, rect2)
    int_area = get_area(get_intersect(rect1, rect2));
    union_area = get_area(rect1) + get_area(rect2) - int_area;
    score = int_area / union_area;
end

function rect = get_intersect(rect1, rect2)
    xmin = max([rect1(1), rect2(1)]);
    ymin = max([rect1(2), rect2(2)]);
    xmax = min([rect1(1) + rect1(3), rect2(1) + rect2(3)]);
    ymax = min([rect1(2) + rect1(4), rect2(2) + rect2(4)]);
    width = max([xmax - xmin, 0]);
    height = max([ymax - ymin, 0]);
    rect = [xmin, ymin, width, height];
end

function area = get_area(rect)
    area = rect(3) * rect(4);
end