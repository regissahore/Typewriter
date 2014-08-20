function [edge] = detect(tree, feature)
    [height, width, ~] = size(feature);
    edge = zeros(height, width);
    for y = 1 : 16 : height - 16 + 1
        for x = 1 : 16 : width - 16 + 1
            edge(y : y + 16 - 1, x : x + 16 - 1) = detect_patch(tree, feature(y : y + 16 - 1, x : x + 16 - 1, :));
        end
    end
end

function [edge_patch] = detect_patch(tree, feature_patch)
    if tree.type == 0
        edge_patch = tree.boundary;
    else
        if tree.type == 1
            decision = feature_patch(tree.x, tree.y, tree.k) > tree.tau;
        elseif tree.type == 2
            decision = feature_patch(tree.x1, tree.y1, tree.k) - feature_patch(tree.x2, tree.y2, tree.k) > tree.tau;
        else
            decision = randi([0 1]);
        end
        if decision == 0
            edge_patch = detect_patch(tree.left, feature_patch);
        else
            edge_patch = detect_patch(tree.right, feature_patch);
        end
    end
end