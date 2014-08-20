function score = get_filter_score(bing, a, beta)
    score = zeros([1, 3]);
    setting = get_setting();
    for k = 1 : 3
        for j = 1 : setting.Nw
            temp_score = 0.0;
            for i = 1 : setting.Ng
                temp_score = temp_score + 2 ^ (8 - i) * ...
                    (2 * count_one(bitand(a(j, k), bing(i, k))) - ...
                    count_one(bing(i, k)));
            end
            score(k) = score(k) + beta(j, k) * temp_score;
        end
    end
end

function num = count_one(bitnum)
    num = 0;
    while bitnum > 0
        bitnum = bitand(bitnum, bitnum - 1);
        num = num + 1;
    end
end