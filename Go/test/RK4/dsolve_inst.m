lambda1 = 0.1;
lambda2 = 0.2;
lambda3 = 0.3;
mu1 = 0.4;
mu2 = 0.5;
mu3 = 0.6;
syms p0(t) p1(t) p2(t) p3(t);
P = dsolve(diff(p0) == -(lambda1 + lambda2 + lambda3) * p0 + mu1 * p1 + mu2 * p2 + mu3 * p3, ...
           diff(p1) == lambda1 * p0 - mu1 * p1, ...
           diff(p2) == lambda2 * p0 - mu2 * p2, ...
           diff(p3) == lambda3 * p0 - mu3 * p3, ...
           p0(0) == 1, ...
           p1(0) == 0, ...
           p2(0) == 0, ...
           p3(0) == 0);
for i = 1 : 100: 1000
    [i subs(real(P.p0), 't', i), subs(real(P.p1), 't', i), subs(real(P.p2), 't', i), subs(real(P.p3), 't', i)]
end