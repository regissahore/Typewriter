function bing = binary_normed_gradient(ng)
    setting = get_setting();
    Ng = setting.Ng;
    height = size(ng, 1);
    width = size(ng, 2);
    r = uint8(zeros([height, width, setting.Ng, 3]));
    b = uint64(zeros([height, width, setting.Ng, 3]));
    for x = 1 : width
        for y = 1 : height
            for k = 1 : 3
                for i = 1 : Ng
                    bit = uint8(0);
                    if bitand(bitshift(uint8(1), 8 - i), ng(y, x, k)) > 0
                        bit = uint8(1);
                    end
                    r(y, x, i, k) = bitor(bitshift(get_safe_r(r, x - 1, y, i, k), 1), bit);
                    b(y, x, i, k) = bitor(bitshift(get_safe_b(b, x, y - 1, i, k), 8), uint64(r(y, x, i, k)));
                end
            end
        end
    end
    bing = b;
end

function ret = get_safe_r(r, x, y, i, k)
    if x == 0 || y == 0
        ret = uint8(0);
    else
        ret = r(y, x, i, k);
    end
end

function ret = get_safe_b(b, x, y, i, k)
    if x == 0 || y == 0
        ret = uint64(0);
    else
        ret = b(y, x, i, k);
    end
end